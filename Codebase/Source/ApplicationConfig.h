/*
  ==============================================================================

    ApplicationConfig.h
    Created: 10 Dec 2016 8:31:26pm
    Author:  hungc

  ==============================================================================
*/

#ifndef APPLICATIONCONFIG_H_INCLUDED
#define APPLICATIONCONFIG_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "ScannerPlugin.h"
#include "XmlUtil.h"
#include <map>

class ApplicationConfig 
{
public:
	enum class Generation {
		CONTRA,
		MSG
	};
public:
	
	static ApplicationConfig &Instance() {
		if (instance == nullptr) {
			instance = new ApplicationConfig();
		} 
		return *instance;
	}

	class SettingConfig {
	private:
		bool isStupidPath(const File& f)
		{
			Array<File> roots;
			File::findFileSystemRoots(roots);

			if (roots.contains(f))
				return true;

			File::SpecialLocationType pathsThatWouldBeStupidToScan[]
				= { File::globalApplicationsDirectory,
				File::userHomeDirectory,
				File::userDocumentsDirectory,
				File::userDesktopDirectory,
				File::tempDirectory,
				File::userMusicDirectory,
				File::userMoviesDirectory,
				File::userPicturesDirectory };

			for (int i = 0; i < numElementsInArray(pathsThatWouldBeStupidToScan); ++i)
			{
				const File sillyFolder(File::getSpecialLocation(pathsThatWouldBeStupidToScan[i]));

				if (f == sillyFolder || sillyFolder.isAChildOf(f))
					return true;
			}

			return false;
		}
	public:
		bool mUseVST;
		bool mUseVST3;
		bool mUseAU;
		Array<String> mPathScanDir;// List of path on setting window;
		//ScopedPointer <FileSearchPath> mSearchPaths;
		SettingConfig() {
			Clear();
		};
		~SettingConfig() {
			mPathScanDir.clear();
		}

		void Clear() {
			mPathScanDir.clear();
			mUseAU = false;
			mUseVST3 = false;
			mUseVST = false;
		};

		FileSearchPath ToSearchPaths() {
			FileSearchPath mSearchPaths;
			for (int i = 0; i < mPathScanDir.size(); i++) {
				File file(mPathScanDir[i]);
				if(!isStupidPath(file))
					mSearchPaths.add(file, i);
			}
			return mSearchPaths;
		};

		XmlElement * ToXml() {
			XmlElement* const e = new XmlElement("SETTING_CONFIG");
			XmlElement* config = e->createNewChildElement("SCAN_CONFIG");
			config->setAttribute("VST", mUseVST);
			config->setAttribute("VST3", mUseVST3);
			config->setAttribute("AU", mUseAU);

			for (int i = 0; i < mPathScanDir.size(); ++i)
				e->createNewChildElement("SCAN_PATHS")->setAttribute("Path", mPathScanDir[i]);

			return e;
		};

		void FromXml(const XmlElement & xml) {
			Clear();

			if (xml.hasTagName("SETTING_CONFIG"))
			{

				forEachXmlChildElement(xml, e)
				{
					PluginDescription info;

					if (e->hasTagName("SCAN_PATHS"))
						mPathScanDir.add(e->getStringAttribute("Path"));
					else if (e->hasTagName("SCAN_CONFIG")) {
						mUseVST = e->getBoolAttribute("VST");
						mUseVST3 = e->getBoolAttribute("VST3");
						mUseAU = e->getBoolAttribute("AU");
					}
				}
			}
		}
	};

	SettingConfig& GetSetting() {
		return mSettingConfig;
	}
	void SetSetting(const SettingConfig setting, bool save = true) {
		mSettingConfig = setting;
		if(save)
			SaveSetting();
	};

	void SetGeneration(Generation mode, bool save= true) {
		mGenerateMode = mode;
		if(save)
			SaveGeneration();
	};
	Generation &GetGeneration() {
		return mGenerateMode;
	};

	File &GetDeathFile() {
		return *mDeadMansPedalFile;
	};

	KnownPluginList &GetKnownPluginList() {
		return *mKnownPluginList;
	};

	void SetSelectManufacture(int idx, bool save = true) {
		if (mGenerateMode == Generation::MSG) {
			mSelectedManuIndexMsg = idx;
			if (save)
				SaveSelectManufactureMsg();
		}
		else if (mGenerateMode == Generation::CONTRA) {
			mSelectedManuIndexContra = idx;
			if (save)
				SaveSelectManufactureContra();
		}
	};
	int &GetSelectManufacture() {
		if (mGenerateMode == Generation::MSG) {
			return mSelectedManuIndexMsg;
		}
		else if (mGenerateMode == Generation::CONTRA) {
			return mSelectedManuIndexContra;
		}
		
	};

	void SetSelectList(SparseSet<int> select, bool save = true) {
		if (mGenerateMode == Generation::MSG) {
			mListSelectedPluginMsg[mSelectedManuIndexMsg] = select;
			if (save)
				SaveSelectCacheMsg();
		}
		else if (mGenerateMode == Generation::CONTRA) {
			mListSelectedPluginContra[mSelectedManuIndexContra] = select;
			if (save)
				SaveSelectCacheContra();
		}
	};
	SparseSet<int> &GetSelectList() {
		if (mGenerateMode == Generation::CONTRA) {
			return mListSelectedPluginContra[mSelectedManuIndexContra];
		}
		else if (mGenerateMode == Generation::MSG) {
			return mListSelectedPluginMsg[mSelectedManuIndexMsg];
		}
	};

	Array<String> &GetManu() {
		return mListManu;
	};
	OwnedArray<PluginDescription> &GetPlugins(String manu) {
		return mListPlugin[manu];
	};

	void Save() {
		SaveSetting();
		SaveGeneration();
		SaveListPlugin();
		SaveSelectManufactureContra();
		SaveSelectManufactureMsg();
		SaveSelectCacheContra();
		SaveSelectCacheMsg();
	};
	void ResetScan() {
		mKnownPluginList->clear();
		ClearList();
	};
	void ClearList() {
		mSelectedManuIndexContra = 0;
		mSelectedManuIndexMsg = 0;
		mListSelectedPluginMsg.clear();
		mListSelectedPluginContra.clear();
		for (std::map<String, OwnedArray<PluginDescription>>::iterator it = mListPlugin.begin(); it != mListPlugin.end(); ++it) {
			it->second.clear(false);
		}
		mListPlugin.clear();
		for (std::map<String, Array<String>>::iterator it = mListPluginName.begin(); it != mListPluginName.end(); ++it) {
			it->second.clear();
		}
		mListPluginName.clear();
		mListManu.clear();
	};
	void ProcessFilter() {
		for (int i = 0; i < mKnownPluginList->getNumTypes(); i++)
		{
			PluginDescription * desc = mKnownPluginList->getType(i);
			mListPlugin[desc->manufacturerName].add(desc);
			char tmp[100] = { 0 };
			sprintf(tmp, "%-35s %-3s", desc->name.toRawUTF8(), desc->pluginFormatName.toRawUTF8());
			mListPluginName[desc->manufacturerName].add(tmp);
		}
		for (std::map<String, Array<String>>::iterator it = mListPluginName.begin(); it != mListPluginName.end(); ++it) {
			mListManu.add(it->first);
		}
	};

	void GenerateSetting() {
		String message = "Settings files for";
		PropertiesFile::Options options;
		if (mGenerateMode == Generation::CONTRA) {
			options.applicationName = "AudioVitaminsContra";
			options.filenameSuffix = "settings";
			options.osxLibrarySubFolder = "Preferences"; // check the correct directory
			message += " Contra created";
		}
		else if (mGenerateMode == Generation::MSG) {
			options.applicationName = "AudioVitaminsMSG";
			options.filenameSuffix = "settings";
			options.osxLibrarySubFolder = "Preferences"; // check the correct directory
			message += " Msg created";
		}

		ApplicationProperties *gAppProperties = new ApplicationProperties();
		gAppProperties->setStorageParameters(options);
		ScopedPointer<KnownPluginList> knownPluginList = new KnownPluginList();
		for (int i = 0; i < mListManu.size(); i++) {
			OwnedArray<PluginDescription> &arr = mListPlugin[mListManu[i]];
			if (mGenerateMode == Generation::MSG) {
				SparseSet<int> &select = mListSelectedPluginMsg[i];
				for (int j = 0; j < select.size(); j++) {
					PluginDescription * des = arr[select[j]];
					if (des != nullptr) {
						knownPluginList->addType(*des);
					}
				}
			}
			else if (mGenerateMode == Generation::CONTRA) {
				SparseSet<int> &select = mListSelectedPluginContra[i];
				for (int j = 0; j < select.size(); j++) {
					PluginDescription * des = arr[select[j]];
					if (des != nullptr) {
						knownPluginList->addType(*des);
					}
				}
			}
			
		}

		KnownPluginList::SortMethod pluginSortMethod = (KnownPluginList::SortMethod)gAppProperties->getUserSettings()->getIntValue("pluginSortMethod", KnownPluginList::sortByManufacturer);
		knownPluginList->sort(pluginSortMethod, true);

		ScopedPointer<XmlElement> savedPluginList(knownPluginList->createXml());
		PropertiesFile*userSettings = gAppProperties->getUserSettings();
		userSettings->setValue("pluginList", savedPluginList);
		gAppProperties->saveIfNeeded();


		NativeMessageBox::showMessageBox(AlertWindow::NoIcon, "", message);
	};
private:
	static ApplicationConfig *instance;

	ApplicationConfig() {
		mSelectedManuIndexContra = -1;
		mSelectedManuIndexMsg = -1;
		PropertiesFile::Options options;
		options.applicationName = "Plugin Manager";
		options.filenameSuffix = "Config";
		options.osxLibrarySubFolder = "Preferences"; // check the correct directory

		mAppProperties = new ApplicationProperties();
		mAppProperties->setStorageParameters(options);

		mKnownPluginList = new KnownPluginList();

		mDeadMansPedalFile = new File();

		LoadListPlugin();
		//Load setting
		LoadSetting();
		//Load GenerationMode
		LoadGeneration();
		//Load cache plugin
		LoadSelectManufacture();
		//
		LoadSelectCache();
		// Process filter after loaded
		ProcessFilter();
	};

	~ApplicationConfig() {
		mAppProperties = nullptr;
		mKnownPluginList = nullptr;
		mDeadMansPedalFile = nullptr;
		delete instance;
	};

	void LoadSetting() {
		PropertiesFile*userSettings = mAppProperties->getUserSettings();
		ScopedPointer<XmlElement> eSetting(userSettings->getXmlValue("Setting"));
		if (eSetting != nullptr) {
			mSettingConfig.FromXml(*eSetting);
		}
		else {
#ifdef WIN32 
			mSettingConfig.mPathScanDir.add("C:\Program Files\VSTPlugins");
            mSettingConfig.mPathScanDir.add("C:\Program Files\Steinberg\VstPlugins");
            mSettingConfig.mPathScanDir.add("C:\Program Files\Common Files\VST3");
#else
			mSettingConfig.mPathScanDir.add("/Library/Audio/Plugins/Components");
			mSettingConfig.mPathScanDir.add("/Library/Audio/Plugins/VST");
			mSettingConfig.mPathScanDir.add("/Library/Audio/Plugins/VST3");
#endif
		}
	};
	void SaveSetting() {
		ScopedPointer<XmlElement> eSetting(mSettingConfig.ToXml());

		if (eSetting != nullptr)
		{
			PropertiesFile*userSettings = mAppProperties->getUserSettings();
			userSettings->setValue("Setting", eSetting);
			mAppProperties->saveIfNeeded();
		}
	};

	void LoadGeneration() {
		PropertiesFile*userSettings = mAppProperties->getUserSettings();
		mGenerateMode = (Generation)userSettings->getIntValue("GenerationMode");
	};
	void SaveGeneration() {
		PropertiesFile* userSettings = mAppProperties->getUserSettings();
		userSettings->setValue("GenerationMode", (int)mGenerateMode);
		mAppProperties->saveIfNeeded();
	};

	void LoadListPlugin() {
		ScopedPointer<XmlElement> pluginList(mAppProperties->getUserSettings()->getXmlValue("PLUGINLIST"));
		if (nullptr != pluginList)
		{
			mKnownPluginList->recreateFromXml(*pluginList);
			pluginList = nullptr;
		}
	};
	void SaveListPlugin() {
		ScopedPointer<XmlElement> savedPluginList(mKnownPluginList->createXml());

		if (savedPluginList != nullptr)
		{
			PropertiesFile*userSettings = mAppProperties->getUserSettings();
			userSettings->setValue("PLUGINLIST", savedPluginList);
			mAppProperties->saveIfNeeded();
		}
	};

	void SaveSelectManufactureContra() {
		PropertiesFile* userSettings = mAppProperties->getUserSettings();
		userSettings->setValue("SELECT_MANUFACTURES_CONTRA", (int)mSelectedManuIndexContra);
		mAppProperties->saveIfNeeded();
	}
	void SaveSelectManufactureMsg() {
		PropertiesFile* userSettings = mAppProperties->getUserSettings();
		userSettings->setValue("SELECT_MANUFACTURES_MSG", (int)mSelectedManuIndexMsg);
		mAppProperties->saveIfNeeded();
	}
	void LoadSelectManufacture() {
		PropertiesFile* userSettings = mAppProperties->getUserSettings();
		mSelectedManuIndexContra = userSettings->getIntValue("SELECT_MANUFACTURES_CONTRA");
		mSelectedManuIndexMsg = userSettings->getIntValue("SELECT_MANUFACTURES_MSG");
	}

	void SaveSelectCacheMsg() {
		XmlElement* const eCache = new XmlElement("SELECT_CACHE");
		eCache->setAttribute("Size", (int)mListSelectedPluginMsg.size());
		for (int i = 0; i < mListSelectedPluginMsg.size(); i++) {
			eCache->addChildElement(XmlUtil::ToXml(mListSelectedPluginMsg[i]));
		}
		PropertiesFile*userSettings = mAppProperties->getUserSettings();
		userSettings->setValue("CACHE_MSG", eCache);
	}

	void SaveSelectCacheContra() {
		XmlElement* const eCache = new XmlElement("SELECT_CACHE");
		eCache->setAttribute("Size", (int)mListSelectedPluginContra.size());
		for (int i = 0; i < mListSelectedPluginContra.size(); i++) {
			eCache->addChildElement(XmlUtil::ToXml(mListSelectedPluginContra[i]));
		}
		PropertiesFile*userSettings = mAppProperties->getUserSettings();
		userSettings->setValue("CACHE_CONTRA", eCache);
	}

	void LoadSelectCache() {
		mListSelectedPluginMsg.clear();
		ScopedPointer<XmlElement> cache1(mAppProperties->getUserSettings()->getXmlValue("CACHE_MSG"));
		if (nullptr != cache1)
		{
			if (cache1->hasTagName("SELECT_CACHE"))
			{
				int i = 0;
				forEachXmlChildElementWithTagName(*cache1, eD, "SparseSetInt") {
					mListSelectedPluginMsg[i++] = XmlUtil::FromXml(eD);
				}
			}
			cache1 = nullptr;
		}
		mListSelectedPluginContra.clear();
		ScopedPointer<XmlElement> cache2(mAppProperties->getUserSettings()->getXmlValue("CACHE_MSG"));
		if (nullptr != cache2)
		{
			if (cache2->hasTagName("SELECT_CACHE"))
			{
				int i = 0;
				forEachXmlChildElementWithTagName(*cache2, eD, "SparseSetInt") {
					mListSelectedPluginContra[i++] = XmlUtil::FromXml(eD);
				}
			}
			cache2 = nullptr;
		}
	};

	//std::map<int, SparseSet<int>> mListSelectedPlugin;
	std::map<int, SparseSet<int>> mListSelectedPluginMsg;
	std::map<int, SparseSet<int>> mListSelectedPluginContra;
	int mSelectedManuIndexContra;
	int mSelectedManuIndexMsg;

	ScopedPointer<ApplicationProperties> mAppProperties;
	Generation mGenerateMode;
	SettingConfig mSettingConfig;
	ScopedPointer<File> mDeadMansPedalFile;
	ScopedPointer<KnownPluginList> mKnownPluginList;
	std::map<String, OwnedArray<PluginDescription>> mListPlugin;
	std::map<String, Array<String>> mListPluginName;
	Array<String> mListManu;
};



#endif  // APPLICATIONCONFIG_H_INCLUDED
