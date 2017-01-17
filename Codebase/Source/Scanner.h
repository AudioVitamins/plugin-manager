/*
  ==============================================================================

    Scanner.h
    Created: 15 Dec 2016 10:35:32pm
    Author:  hungc

  ==============================================================================
*/

#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED
#include "ApplicationConfig.h"

class Scanner:
	public  ScannerPluginListener,
	public Timer,
	public ChangeListener
{
	ApplicationConfig &mApp;
	AudioPluginFormatManager mFormatManager;
	double mProgressPercent;
	String mScanMsg;
	int mIndex;
	bool mFinished;
	void scanPluginStarted(ScannerPlugin *source, String type) override {
		mMessage += type + ": ";
	};
	void scanPluginFinished(ScannerPlugin *source, String type) override {
		mMessage += "Finished\n";
		NextScan();
	};

	void timerCallback() override {
		if (mScaner != nullptr) {
			mProgressPercent = mScaner->getProgress();
			mScanMsg = mMessage + mScaner->getScanMsg();
		}
	
		mProgress.setMessage(mScanMsg);
		if (mFinished) {
			mProgress.setVisible(false);
			stopTimer();
		}
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		for (int i = 0; i < mListeners.size(); i++) {
			mListeners.getUnchecked(i)->updateScan();
		}
	};
public:
	class Listener {
	public:
		virtual void updateScan() = 0;
		virtual void finishedScan() = 0;
        virtual ~Listener() {};
	};
private:
	String mMessage;
	AlertWindow mProgress;
	OwnedArray<Listener> mListeners;
	ScannerPlugin *mScaner;
public:
	void addScanListener(Listener * listener) {
		mListeners.add(listener);
	};
	void removeScanListener(Listener * listener) {
		for (int i = 0; i < mListeners.size(); i++) {
			if (mListeners.getUnchecked(i) == listener) {
				mListeners.remove(i);
				break;
			}
		}
	};

	Scanner(ApplicationConfig &app): mApp(app), mProgressPercent(0), mIndex(-1), mProgress("Scanning plugin", "", AlertWindow::NoIcon){
		mFormatManager.addDefaultFormats();
		mMessage = "";
		mFinished = true;
		mScaner = nullptr;
	};
	~Scanner() {
		if(mScaner != nullptr)
			delete mScaner;
	};
	void ScanPlugin() {
		mProgress.addProgressBarComponent(mProgressPercent);
		mProgress.enterModalState();
		mProgress.setAlwaysOnTop(true);
		mFinished = false;
		startTimer(30);
		mApp.GetKnownPluginList().clear();
		mApp.GetKnownPluginList().removeAllChangeListeners();
		mApp.GetKnownPluginList().addChangeListener(this);
		NextScan();
	};

	void NextScan() {
		AudioPluginFormat* format = nullptr;
		mIndex++;
		if (mIndex < mFormatManager.getNumFormats()) {
			format = mFormatManager.getFormat(mIndex);
		}
		else {
			for (int i = 0; i < mListeners.size(); i++) {
				mListeners.getUnchecked(i)->finishedScan();
			}
			mProgress.removeFromDesktop();
			mFinished = true;
			return;
		}

		if (format != nullptr
            && ((format->getName() == "VST" && mApp.GetSetting().mUseVST)
                || (format->getName() == "VST3" && mApp.GetSetting().mUseVST3)
                || (format->getName() == "AudioUnit" && mApp.GetSetting().mUseAU))) {
			mScaner = new ScannerPlugin(
				mApp.GetKnownPluginList(),
				*format,
				mApp.GetSetting().ToSearchPaths(),
				mApp.GetDeathFile(),
				nullptr,
				true, 6);
			mScaner->addScanListener(this);
			mScaner->Scan();
		}
		else {
			NextScan();
		}
	};
};

	typedef	Scanner::Listener ScannerListener;

#endif  // SCANNER_H_INCLUDED
