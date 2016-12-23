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
//[/Headers]

#include "ListBoxComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
Array<String> ListBoxComponent::sListStrings = Array<String>();
ListBoxComponent::ListBoxComponent(OwnedArray<PluginDescription> &listPlugins):mListStrings(ListBoxComponent::sListStrings) {
	mCheckList = LIST_PLUGIN_CHECK_BOX;
	mHeaderCheckBox = new HeaderComponent(this);
	//[/Constructor_pre]

	addAndMakeVisible(listBox = new CustomListBox());
	listBox->setName(CharPointer_UTF8("L\xc3\xadst Box"));

	listBox->setMultipleSelectionEnabled(true);
	listBox->setClickingTogglesRowSelection(true);
	listBox->setHeaderComponent(mHeaderCheckBox);

	mPluginCheckBoxData = new PluginCheckBoxModel(this, listPlugins);
	listBox->setModel(mCheckBoxData);

	setSize(348, 384);
};
//[/MiscUserDefs]

//==============================================================================
ListBoxComponent::ListBoxComponent (Array<String> &listStrings, bool check)
    : mListStrings(listStrings)
{
    //[Constructor_pre] You can add your own custom stuff here..
	if (check) {
		mCheckList = LIST_STRING_CHECK_BOX;
	}
	else {
		mCheckList = LIST_STRING;
	}
	mHeaderCheckBox = new HeaderComponent(this);
    //[/Constructor_pre]

    addAndMakeVisible (listBox = new CustomListBox());
    listBox->setName (CharPointer_UTF8 ("L\xc3\xadst Box"));


    //[UserPreSize]

	if (mCheckList == LIST_STRING_CHECK_BOX) {
		listBox->setMultipleSelectionEnabled(true);
		listBox->setClickingTogglesRowSelection(true);
		listBox->setHeaderComponent(mHeaderCheckBox);

		mCheckBoxData = new StringCheckBoxModel(this, listStrings);
		listBox->setModel(mCheckBoxData);
	}
	else {
		mData = new StringModel(this, listStrings);
		listBox->setModel(mData);
	}

    //[/UserPreSize]

    setSize (348, 384);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ListBoxComponent::~ListBoxComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//mHeaderCheckBox = nullptr;
	mCheckBoxData = nullptr;
	mData = nullptr;
	mPluginCheckBoxData = nullptr;
    //[/Destructor_pre]

    listBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ListBoxComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	g.fillAll(Colour::fromFloatRGBA(0.0f, 0.0f, 0.0f, 0.0f));
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ListBoxComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    listBox->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ListBoxComponent::UpdateList() {
	listBox->setModel(nullptr);
	switch (mCheckList)
	{
	case LIST_PLUGIN_CHECK_BOX:
		listBox->setModel(mPluginCheckBoxData);
		break;
	case LIST_STRING:
		listBox->setModel(mData);
		break;
	case LIST_STRING_CHECK_BOX:
		listBox->setModel(mCheckBoxData);
		break;

	default:
		break;
	}

	listBox->updateContent();
	listBox->repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ListBoxComponent" componentName=""
                 parentClasses="public Component" constructorParams="Array&lt;String&gt; &amp;listStrings, bool check"
                 variableInitialisers="mListStrings(listStrings)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="348" initialHeight="384">
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="L&#237;st Box" id="d2bb58fea7bbc445" memberName="listBox"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 100%" class="CustomListBox"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: pluginmanager_checkbox_empty_button_png, 1014, "../../../Graphics/pluginmanager_checkbox_empty_button.png"
static const unsigned char resource_ListBoxComponent_pluginmanager_checkbox_empty_button_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,11,8,2,0,0,0,38,206,224,113,0,0,0,25,116,
69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,3,108,105,84,88,116,88,77,76,58,99,111,109,46,97,100,111,98,101,46,120,109,112,0,0,
0,0,0,60,63,120,112,97,99,107,101,116,32,98,101,103,105,110,61,34,239,187,191,34,32,105,100,61,34,87,53,77,48,77,112,67,101,104,105,72,122,114,101,83,122,78,84,99,122,107,99,57,100,34,63,62,32,60,120,
58,120,109,112,109,101,116,97,32,120,109,108,110,115,58,120,61,34,97,100,111,98,101,58,110,115,58,109,101,116,97,47,34,32,120,58,120,109,112,116,107,61,34,65,100,111,98,101,32,88,77,80,32,67,111,114,101,
32,53,46,53,45,99,48,49,52,32,55,57,46,49,53,49,52,56,49,44,32,50,48,49,51,47,48,51,47,49,51,45,49,50,58,48,57,58,49,53,32,32,32,32,32,32,32,32,34,62,32,60,114,100,102,58,82,68,70,32,120,109,108,110,115,
58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,62,32,60,114,100,102,58,68,
101,115,99,114,105,112,116,105,111,110,32,114,100,102,58,97,98,111,117,116,61,34,34,32,120,109,108,110,115,58,120,109,112,77,77,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,
47,120,97,112,47,49,46,48,47,109,109,47,34,32,120,109,108,110,115,58,115,116,82,101,102,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,115,84,121,
112,101,47,82,101,115,111,117,114,99,101,82,101,102,35,34,32,120,109,108,110,115,58,120,109,112,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,34,
32,120,109,112,77,77,58,79,114,105,103,105,110,97,108,68,111,99,117,109,101,110,116,73,68,61,34,120,109,112,46,100,105,100,58,48,55,56,48,49,49,55,52,48,55,50,48,54,56,49,49,56,67,49,52,68,69,48,68,65,
55,70,69,50,51,52,57,34,32,120,109,112,77,77,58,68,111,99,117,109,101,110,116,73,68,61,34,120,109,112,46,100,105,100,58,50,50,54,57,51,67,51,50,51,54,49,53,49,49,69,54,57,54,56,55,56,67,49,50,66,53,57,
48,55,50,48,53,34,32,120,109,112,77,77,58,73,110,115,116,97,110,99,101,73,68,61,34,120,109,112,46,105,105,100,58,50,50,54,57,51,67,51,49,51,54,49,53,49,49,69,54,57,54,56,55,56,67,49,50,66,53,57,48,55,
50,48,53,34,32,120,109,112,58,67,114,101,97,116,111,114,84,111,111,108,61,34,65,100,111,98,101,32,80,104,111,116,111,115,104,111,112,32,67,83,54,32,40,77,97,99,105,110,116,111,115,104,41,34,62,32,60,120,
109,112,77,77,58,68,101,114,105,118,101,100,70,114,111,109,32,115,116,82,101,102,58,105,110,115,116,97,110,99,101,73,68,61,34,120,109,112,46,105,105,100,58,55,97,50,48,100,102,101,54,45,48,51,48,48,45,
52,50,50,49,45,98,100,102,56,45,100,99,99,98,52,52,53,101,51,48,53,54,34,32,115,116,82,101,102,58,100,111,99,117,109,101,110,116,73,68,61,34,120,109,112,46,100,105,100,58,48,55,56,48,49,49,55,52,48,55,
50,48,54,56,49,49,56,67,49,52,68,69,48,68,65,55,70,69,50,51,52,57,34,47,62,32,60,47,114,100,102,58,68,101,115,99,114,105,112,116,105,111,110,62,32,60,47,114,100,102,58,82,68,70,62,32,60,47,120,58,120,
109,112,109,101,116,97,62,32,60,63,120,112,97,99,107,101,116,32,101,110,100,61,34,114,34,63,62,43,172,3,54,0,0,0,32,73,68,65,84,120,218,98,220,184,113,35,3,126,128,95,5,80,150,137,129,16,24,89,42,24,9,
134,41,64,128,1,0,145,36,8,95,128,195,154,248,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ListBoxComponent::pluginmanager_checkbox_empty_button_png = (const char*) resource_ListBoxComponent_pluginmanager_checkbox_empty_button_png;
const int ListBoxComponent::pluginmanager_checkbox_empty_button_pngSize = 1014;

// JUCER_RESOURCE: pluginmanager_checkbox_greyfill_button_png, 1020, "../../../Graphics/pluginmanager_checkbox_greyfill_button.png"
static const unsigned char resource_ListBoxComponent_pluginmanager_checkbox_greyfill_button_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,11,8,2,0,0,0,38,206,224,113,0,0,0,25,
116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,3,108,105,84,88,116,88,77,76,58,99,111,109,46,97,100,111,98,101,46,120,109,112,
0,0,0,0,0,60,63,120,112,97,99,107,101,116,32,98,101,103,105,110,61,34,239,187,191,34,32,105,100,61,34,87,53,77,48,77,112,67,101,104,105,72,122,114,101,83,122,78,84,99,122,107,99,57,100,34,63,62,32,60,
120,58,120,109,112,109,101,116,97,32,120,109,108,110,115,58,120,61,34,97,100,111,98,101,58,110,115,58,109,101,116,97,47,34,32,120,58,120,109,112,116,107,61,34,65,100,111,98,101,32,88,77,80,32,67,111,114,
101,32,53,46,53,45,99,48,49,52,32,55,57,46,49,53,49,52,56,49,44,32,50,48,49,51,47,48,51,47,49,51,45,49,50,58,48,57,58,49,53,32,32,32,32,32,32,32,32,34,62,32,60,114,100,102,58,82,68,70,32,120,109,108,110,
115,58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,62,32,60,114,100,102,58,
68,101,115,99,114,105,112,116,105,111,110,32,114,100,102,58,97,98,111,117,116,61,34,34,32,120,109,108,110,115,58,120,109,112,77,77,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,
109,47,120,97,112,47,49,46,48,47,109,109,47,34,32,120,109,108,110,115,58,115,116,82,101,102,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,115,84,
121,112,101,47,82,101,115,111,117,114,99,101,82,101,102,35,34,32,120,109,108,110,115,58,120,109,112,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,
47,34,32,120,109,112,77,77,58,79,114,105,103,105,110,97,108,68,111,99,117,109,101,110,116,73,68,61,34,120,109,112,46,100,105,100,58,48,55,56,48,49,49,55,52,48,55,50,48,54,56,49,49,56,67,49,52,68,69,48,
68,65,55,70,69,50,51,52,57,34,32,120,109,112,77,77,58,68,111,99,117,109,101,110,116,73,68,61,34,120,109,112,46,100,105,100,58,53,65,70,65,52,48,57,57,51,54,49,53,49,49,69,54,57,54,56,55,56,67,49,50,66,
53,57,48,55,50,48,53,34,32,120,109,112,77,77,58,73,110,115,116,97,110,99,101,73,68,61,34,120,109,112,46,105,105,100,58,53,65,70,65,52,48,57,56,51,54,49,53,49,49,69,54,57,54,56,55,56,67,49,50,66,53,57,
48,55,50,48,53,34,32,120,109,112,58,67,114,101,97,116,111,114,84,111,111,108,61,34,65,100,111,98,101,32,80,104,111,116,111,115,104,111,112,32,67,83,54,32,40,77,97,99,105,110,116,111,115,104,41,34,62,32,
60,120,109,112,77,77,58,68,101,114,105,118,101,100,70,114,111,109,32,115,116,82,101,102,58,105,110,115,116,97,110,99,101,73,68,61,34,120,109,112,46,105,105,100,58,55,97,50,48,100,102,101,54,45,48,51,48,
48,45,52,50,50,49,45,98,100,102,56,45,100,99,99,98,52,52,53,101,51,48,53,54,34,32,115,116,82,101,102,58,100,111,99,117,109,101,110,116,73,68,61,34,120,109,112,46,100,105,100,58,48,55,56,48,49,49,55,52,
48,55,50,48,54,56,49,49,56,67,49,52,68,69,48,68,65,55,70,69,50,51,52,57,34,47,62,32,60,47,114,100,102,58,68,101,115,99,114,105,112,116,105,111,110,62,32,60,47,114,100,102,58,82,68,70,62,32,60,47,120,58,
120,109,112,109,101,116,97,62,32,60,63,120,112,97,99,107,101,116,32,101,110,100,61,34,114,34,63,62,237,244,75,115,0,0,0,38,73,68,65,84,120,218,98,220,184,113,35,3,94,192,2,196,86,86,86,184,164,143,29,
59,198,196,64,8,140,44,21,140,4,195,20,32,192,0,8,205,7,61,243,252,253,235,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ListBoxComponent::pluginmanager_checkbox_greyfill_button_png = (const char*) resource_ListBoxComponent_pluginmanager_checkbox_greyfill_button_png;
const int ListBoxComponent::pluginmanager_checkbox_greyfill_button_pngSize = 1020;


//[EndFile] You can add extra defines here...
//[/EndFile]
