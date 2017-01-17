/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_CB87035FA43504BB__
#define __JUCE_HEADER_CB87035FA43504BB__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Scanner.h"
//[/Headers]

#include "ListBoxComponent.h"
#include "ListBoxComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainContentComponent  : public Component,
                              public ScannerListener,
                              public ListBoxListener,
                              public ButtonListener
{
public:
    //==============================================================================
    MainContentComponent ();
    ~MainContentComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void updateCache();
	void finishedScan() override;
	void updateScan() override;
	void selectedRowsChanged(ListBoxComponent *source, int lastRowSelected) override;
	void listBoxItemClicked(ListBoxComponent *source, int row, const MouseEvent& e) override;
	void listBoxItemDoubleClicked(ListBoxComponent *source, int row, const MouseEvent& e) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* pluginmanager_background_uismaller_png;
    static const int pluginmanager_background_uismaller_pngSize;
    static const char* contraonbutton_png;
    static const int contraonbutton_pngSize;
    static const char* msgoffbutton_png;
    static const int msgoffbutton_pngSize;
    static const char* msgonbutton_png;
    static const int msgonbutton_pngSize;
    static const char* createbutton_png;
    static const int createbutton_pngSize;
    static const char* scanbutton_png;
    static const int scanbutton_pngSize;
    static const char* settingsbutton_png;
    static const int settingsbutton_pngSize;
    static const char* contraoffbutton_png;
    static const int contraoffbutton_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Array<String> mListManu;
	Array<String> mListPlugin;
	OwnedArray<PluginDescription> mListPlugins;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ImageButton> btnContra;
    ScopedPointer<ImageButton> btnMsg;
    ScopedPointer<ImageButton> btnCreate;
    ScopedPointer<ImageButton> btnSetting;
    ScopedPointer<ImageButton> btnScan;
    ScopedPointer<ListBoxComponent> lbxManufacture;
    ScopedPointer<ListBoxComponent> lbxPlugin;
    Image cachedImage_pluginmanager_background_uismaller_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB87035FA43504BB__
