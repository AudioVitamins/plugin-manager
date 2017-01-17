/*
  ==============================================================================

    ScanerPlugin.h
    Created: 13 Dec 2016 6:22:39pm
    Author:  hungc

  ==============================================================================
*/

#ifndef SCANERPLUGIN_H_INCLUDED
#define SCANERPLUGIN_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "ApplicationConfig.h"
class ScannerPlugin : private Timer
{
public:
	class Listener {
	public:
		virtual void scanPluginStarted(ScannerPlugin *source, String type) = 0;
		virtual void scanPluginFinished(ScannerPlugin *source, String type) = 0;
        
        virtual ~Listener(){};
	};
private:
	OwnedArray<Listener> mListeners;
public:
	void addScanListener(Listener* listener) {
		mListeners.add(listener);
	}; 
	void removeScanListener(Listener* listener) {
		for (int i = 0; i < mListeners.size(); i++) {
			if (mListeners.getUnchecked(i) == listener) {
				mListeners.remove(i);
				break;
			}
		}
	}
public:
	ScannerPlugin(KnownPluginList &knownPluginList,
		AudioPluginFormat& format,
		FileSearchPath searchPaths,
		File &deathFile,
		PropertiesFile* properties,
		bool allowPluginsWhichRequireAsynchronousInstantiation,
		int threads = 5):
		mKnownPluginList(knownPluginList),
		mFormatToScan(format), 
		mSearchPaths(searchPaths),
		mDeathFile(deathFile),
		propertiesToUse(properties),
		progress(0.0), numThreads(threads), allowAsync(allowPluginsWhichRequireAsynchronousInstantiation),
		finished(false)
	{
		// You need to use at least one thread when scanning plug-ins asynchronously
	}

	void Scan(){
		startScan();
	};

	double getProgress() {
		return progress;
	};

	String getScanMsg() {
		return pluginBeingScanned;
	};

	~ScannerPlugin()
	{
		if (pool != nullptr)
		{
			pool->removeAllJobs(true, 60000);
			pool = nullptr;
		}
		scanner = nullptr;
		mListeners.clear(false);
		stopTimer();
	}

private:
	KnownPluginList &mKnownPluginList;
	AudioPluginFormat& mFormatToScan;
	FileSearchPath mSearchPaths;
	File &mDeathFile;
	PropertiesFile* propertiesToUse;
	ScopedPointer<PluginDirectoryScanner> scanner;
	String pluginBeingScanned;
	double progress;
	int numThreads;
	bool allowAsync, finished;
	ScopedPointer<ThreadPool> pool;

	void startScan()
	{
		jassert(!allowAsync || (numThreads > 0));
		scanner = new PluginDirectoryScanner(mKnownPluginList, mFormatToScan, mSearchPaths,
			true, mDeathFile, allowAsync);
		for (int i = 0; i < mListeners.size(); i++) {
			mListeners.getUnchecked(i)->scanPluginStarted(this, mFormatToScan.getName());
		}

		if (numThreads > 0)
		{
			pool = new ThreadPool(numThreads);

			for (int i = numThreads; --i >= 0;)
				pool->addJob(new ScanJob(*this), true);
		}

		startTimer(20);
	}

	void finishedScan()
	{
		stopTimer();

		for (int i = 0; i < mListeners.size(); i++) {
			mListeners.getUnchecked(i)->scanPluginFinished(this, mFormatToScan.getName());
		}
	}

	void timerCallback() override
	{
		if (pool == nullptr)
		{
			if (doNextScan())
				startTimer(20);
		}

		// Using timer to check if finish scaning
		if (finished)
			finishedScan();
	}

	bool doNextScan()
	{
		if (scanner->scanNextFile(true, pluginBeingScanned))
		{
			progress = scanner->getProgress();
			return true;
		}

		finished = true;
		return false;
	}

	struct ScanJob : public ThreadPoolJob
	{
		ScanJob(ScannerPlugin& s) : ThreadPoolJob("pluginscan"), scanner(s) {}

		JobStatus runJob()
		{
			while (scanner.doNextScan() && !shouldExit())
			{
			}

			return jobHasFinished;
		}

		ScannerPlugin& scanner;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScanJob)
	};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScannerPlugin)
};

typedef  ScannerPlugin::Listener ScannerPluginListener;
#endif  // SCANERPLUGIN_H_INCLUDED
