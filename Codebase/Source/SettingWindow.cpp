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

//[Headers] You can add your own extra header files here...
#include "SettingComponent.h"
//[/Headers]

#include "SettingWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginWindow::PluginWindow (Component* const uiComp, const bool isGeneric)
    : DocumentWindow(uiComp->getName(), Colours::lightblue,
      DocumentWindow::closeButton)
{
    //[Constructor_pre] You can add your own custom stuff here..
	centreWithSize(getWidth(), getHeight());
	setUsingNativeTitleBar(true);

    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (411, 252);


    //[Constructor] You can add your own custom stuff here..
	//Component *uiComp = new SettingComponent();
	setContentOwned(uiComp, true);
	//addAndMakeVisible(uiComp);
	setVisible(true);
	if(ComponentPeer* const peer = getPeer())
	{
		peer->setVisible(true);
	}
    //[/Constructor]
}

PluginWindow::~PluginWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginWindow" componentName=""
                 parentClasses="public DocumentWindow" constructorParams="Component* const uiComp, const bool isGeneric"
                 variableInitialisers="DocumentWindow(uiComp-&gt;getName(), Colours::lightblue,&#10;&#9;&#9;DocumentWindow::closeButton)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="411" initialHeight="252">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
