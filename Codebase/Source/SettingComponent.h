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

#ifndef __JUCE_HEADER_797198081B1C719A__
#define __JUCE_HEADER_797198081B1C719A__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "ApplicationConfig.h"
//[/Headers]

#include "ListBoxComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SettingComponent  : public Component,
                          public ButtonListener
{
public:
    //==============================================================================
    SettingComponent ();
    ~SettingComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* pluginmanagersettingsbackgroundui_png;
    static const int pluginmanagersettingsbackgroundui_pngSize;
    static const char* pluginmanager_checkbox_empty_button_png;
    static const int pluginmanager_checkbox_empty_button_pngSize;
    static const char* pluginmanager_checkbox_greyfill_button_png;
    static const int pluginmanager_checkbox_greyfill_button_pngSize;
    static const char* settingsaddfolderbutton_png;
    static const int settingsaddfolderbutton_pngSize;
    static const char* settingsremovefolderbutton_png;
    static const int settingsremovefolderbutton_pngSize;
    static const char* settingsokbutton_png;
    static const int settingsokbutton_pngSize;
    static const char* settingscancelbutton_png;
    static const int settingscancelbutton_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ApplicationConfig::SettingConfig mSetting;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> tgbAu;
    ScopedPointer<ToggleButton> tgbVst;
    ScopedPointer<ToggleButton> tgbVst3;
    ScopedPointer<ImageButton> btnAddFolder;
    ScopedPointer<ImageButton> btnRemoveFolder;
    ScopedPointer<ImageButton> btnOk;
    ScopedPointer<ImageButton> btnCancel;
    ScopedPointer<ListBoxComponent> component;
    Image cachedImage_pluginmanagersettingsbackgroundui_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_797198081B1C719A__
