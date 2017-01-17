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

#ifndef __JUCE_HEADER_937F5D56504737B0__
#define __JUCE_HEADER_937F5D56504737B0__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "HeaderComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ListBoxComponent : public Component
{
public:
	//==============================================================================
	ListBoxComponent(Array<String> &listStrings, bool check);
	~ListBoxComponent();

	//==============================================================================
	//[UserMethods]     -- You can add your own custom methods in this section.
	ListBoxComponent(OwnedArray<PluginDescription> &listPlugins);
	enum ModelType {
		LIST_STRING,
		LIST_STRING_CHECK_BOX,
		LIST_PLUGIN_CHECK_BOX
	};

	SparseSet<int> getSelectedRows() {
		return listBox->getSelectedRows();
	};

	int getNumSelectedRows() {
		return listBox->getNumSelectedRows();
	};

	void setSelectedRows(const SparseSet<int>& setOfRowsToBeSelected,
		NotificationType sendNotificationEventToModel = sendNotification) {
		listBox->setSelectedRows(setOfRowsToBeSelected, sendNotificationEventToModel);
	};

	void selectRow(int rowNumber,
		bool dontScrollToShowThisRow = false,
		bool deselectOthersFirst = true) {
		listBox->selectRow(rowNumber, dontScrollToShowThisRow, deselectOthersFirst);
	};
	void selectAllRows() {
		listBox->selectRangeOfRows(0, mListStrings.size());
	}

	void deselectAllRows() {
		listBox->deselectAllRows();
	};

	void selectRangeOfRows(int firstRow, int lastRow) {
		listBox->selectRangeOfRows(firstRow, lastRow);
	};

	void UpdateList();

	class StringModel : public ListBoxModel {
		Array<String> &mListStrings;
		ListBoxComponent *mOwner;
	public:
		StringModel(ListBoxComponent *own, Array<String> &listStrings) : ListBoxModel(), mListStrings(listStrings), mOwner(own) {

		};

		~StringModel() {
		};

		int getNumRows() override {
			return mListStrings.size();
		}

		void paintListBoxItem(int rowNumber,
			Graphics& g,
			int width, int height,
			bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);

			String someData = mListStrings[rowNumber];

			g.setColour(Colours::white);
			g.drawText(someData, 4, 0, width - 4, height, Justification::centredLeft, true);

		};

		Component* refreshComponentForRow(int rowNumber, bool isRowSelected,
			Component* existingComponentToUpdate) override {
			return existingComponentToUpdate;
		};

		void selectedRowsChanged(int lastRowSelected) override {
			mOwner->selectedRowsChanged(mOwner, lastRowSelected);
		};

		void listBoxItemClicked(int row, const MouseEvent& e) override {
			mOwner->listBoxItemClicked(mOwner, row, e);
		};

		void listBoxItemDoubleClicked(int row, const MouseEvent& e) override {
			mOwner->listBoxItemDoubleClicked(mOwner, row, e);
		};

	};

	class StringCheckBoxModel : public ListBoxModel {
		Array<String> &mListStrings;
		Image uncheckBox, checkBox;
		ListBoxComponent *mOwner;
	public:
		StringCheckBoxModel(ListBoxComponent *own, Array<String> &listStrings) : ListBoxModel(), mListStrings(listStrings), mOwner(own) {
			uncheckBox = ImageCache::getFromMemory(ListBoxComponent::pluginmanager_checkbox_empty_button_png, ListBoxComponent::pluginmanager_checkbox_empty_button_pngSize);
			checkBox = ImageCache::getFromMemory(ListBoxComponent::pluginmanager_checkbox_greyfill_button_png, ListBoxComponent::pluginmanager_checkbox_greyfill_button_pngSize);
		};

		~StringCheckBoxModel() {
		};

		int getNumRows() override {
			return mListStrings.size();
		}

		void paintListBoxItem(int rowNumber,
			Graphics& g,
			int width, int height,
			bool rowIsSelected) override {
			//if (rowIsSelected)
			//	g.fillAll(Colours::lightblue);

			String someData = mListStrings[rowNumber];

			g.setColour(Colours::white);

			int y = height - 16;
			int x = 4;
			if (rowIsSelected) {
				g.drawImage(checkBox, x, y, 11, 11, 0, 0, 11, 11);
			}
			else {
				g.drawImage(uncheckBox, x, y, 11, 11, 0, 0, 11, 11);
			}
			g.drawText(someData, x + 11 + 4, 0, width - 4, height, Justification::centredLeft, true);

		};

		Component* refreshComponentForRow(int rowNumber, bool isRowSelected,
			Component* existingComponentToUpdate) override {
			return existingComponentToUpdate;
		};

		void selectedRowsChanged(int lastRowSelected) override {
			mOwner->selectedRowsChanged(mOwner, lastRowSelected);
		};

		void listBoxItemClicked(int row, const MouseEvent& e) override {
			mOwner->listBoxItemClicked(mOwner, row, e);
		};

		void listBoxItemDoubleClicked(int row, const MouseEvent& e) override {
			mOwner->listBoxItemDoubleClicked(mOwner, row, e);
		};

	};

	class PluginCheckBoxModel : public ListBoxModel {
		//Array<String> &mListStrings;
		OwnedArray<PluginDescription> &mListPlugins;
		Image uncheckBox, checkBox;
		ListBoxComponent *mOwner;
	public:
		PluginCheckBoxModel(ListBoxComponent *own, OwnedArray<PluginDescription> &listPlugins) : ListBoxModel(), mOwner(own), mListPlugins(listPlugins) {
			uncheckBox = ImageCache::getFromMemory(ListBoxComponent::pluginmanager_checkbox_empty_button_png, ListBoxComponent::pluginmanager_checkbox_empty_button_pngSize);
			checkBox = ImageCache::getFromMemory(ListBoxComponent::pluginmanager_checkbox_greyfill_button_png, ListBoxComponent::pluginmanager_checkbox_greyfill_button_pngSize);
		};

		~PluginCheckBoxModel() {
		};

		int getNumRows() override {
			return mListPlugins.size();
		}

		void paintListBoxItem(int rowNumber,
			Graphics& g,
			int width, int height,
			bool rowIsSelected) override {
			//if (rowIsSelected)
			//	g.fillAll(Colours::lightblue);

			PluginDescription *plugin = mListPlugins[rowNumber];

			g.setColour(Colours::white);

			int y = height - 16;
			int x = 4;
			if (rowIsSelected) {
				g.drawImage(checkBox, x, y, 11, 11, 0, 0, 11, 11);
			}
			else {
				g.drawImage(uncheckBox, x, y, 11, 11, 0, 0, 11, 11);
			}
			g.drawText(plugin->name, x + 11 + 4, 0, width - 4 - 50, height, Justification::centredLeft, true);
            String formatName = plugin->pluginFormatName;
            if(formatName == "AudioUnit") {
               formatName = "AU";
            }
			g.drawText(formatName, x + 11 + 4 + width - 4 - 50, 0, width - 4, height, Justification::centredLeft, true);

		};

		Component* refreshComponentForRow(int rowNumber, bool isRowSelected,
			Component* existingComponentToUpdate) override {
			return existingComponentToUpdate;
		};

		void selectedRowsChanged(int lastRowSelected) override {
			mOwner->selectedRowsChanged(mOwner, lastRowSelected);
		};

		void listBoxItemClicked(int row, const MouseEvent& e) override {
			mOwner->listBoxItemClicked(mOwner, row, e);
		};

		void listBoxItemDoubleClicked(int row, const MouseEvent& e) override {
			mOwner->listBoxItemDoubleClicked(mOwner, row, e);
		};

	};

	class CustomListBox : public ListBox {

	public:
		class LookAndFeelMethod :public LookAndFeel_V2 {
		public:
			LookAndFeelMethod() {};
			~LookAndFeelMethod() {};
			void drawScrollbarButton(Graphics& g, ScrollBar& scrollbar,
				int width, int height, int buttonDirection,
				bool /*isScrollbarVertical*/,
				bool /*isMouseOverButton*/,
				bool isButtonDown) override
			{
				Path p;

				if (buttonDirection == 0)
					p.addTriangle(width * 0.5f, height * 0.2f,
						width * 0.1f, height * 0.7f,
						width * 0.9f, height * 0.7f);
				else if (buttonDirection == 1)
					p.addTriangle(width * 0.8f, height * 0.5f,
						width * 0.3f, height * 0.1f,
						width * 0.3f, height * 0.9f);
				else if (buttonDirection == 2)
					p.addTriangle(width * 0.5f, height * 0.8f,
						width * 0.1f, height * 0.3f,
						width * 0.9f, height * 0.3f);
				else if (buttonDirection == 3)
					p.addTriangle(width * 0.2f, height * 0.5f,
						width * 0.7f, height * 0.1f,
						width * 0.7f, height * 0.9f);

				if (isButtonDown)
					g.setColour(Colours::red/*scrollbar.findColour(ScrollBar::thumbColourId).contrasting(0.2f)*/);
				else
					g.setColour(Colours::white/*scrollbar.findColour(ScrollBar::thumbColourId)*/);

				g.fillPath(p);

				g.setColour(Colour(0x80000000));
				g.strokePath(p, PathStrokeType(0.5f));
			};

			void drawScrollbar(Graphics& g,
				ScrollBar& scrollbar,
				int x, int y,
				int width, int height,
				bool isScrollbarVertical,
				int thumbStartPosition,
				int thumbSize,
				bool /*isMouseOver*/,
				bool /*isMouseDown*/) override
			{
				g.fillAll(scrollbar.findColour(ScrollBar::backgroundColourId));

				Path slotPath, thumbPath;

				const float slotIndent = jmin(width, height) > 15 ? 1.0f : 0.0f;
				const float slotIndentx2 = slotIndent * 2.0f;
				const float thumbIndent = slotIndent + 1.0f;
				const float thumbIndentx2 = thumbIndent * 2.0f;

				float gx1 = 0.0f, gy1 = 0.0f, gx2 = 0.0f, gy2 = 0.0f;
				float width_slot = 2;
				if (isScrollbarVertical)
				{
					slotPath.addRoundedRectangle(x + width / 2 - width_slot / 2,
						y,
						width_slot,
						height,
						0);

					if (thumbSize > 0)
						thumbPath.addRoundedRectangle(x + thumbIndent,
							thumbStartPosition + thumbIndent,
							width - thumbIndentx2,
							thumbSize - thumbIndentx2,
							0);
					gx1 = (float)x;
					gx2 = x + width * 0.7f;
				}
				else
				{
					slotPath.addRoundedRectangle(x + slotIndent,
						y + slotIndent,
						width - slotIndentx2,
						height - slotIndentx2,
						(height - slotIndentx2) * 0.5f);

					if (thumbSize > 0)
						thumbPath.addRoundedRectangle(thumbStartPosition + thumbIndent,
							y + thumbIndent,
							thumbSize - thumbIndentx2,
							height - thumbIndentx2,
							(height - thumbIndentx2) * 0.5f);
					gy1 = (float)y;
					gy2 = y + height * 0.7f;
				}

				const Colour thumbColour(scrollbar.findColour(ScrollBar::thumbColourId));
				Colour trackColour1, trackColour2;

				if (scrollbar.isColourSpecified(ScrollBar::trackColourId)
					|| isColourSpecified(ScrollBar::trackColourId))
				{
					trackColour1 = trackColour2 = scrollbar.findColour(ScrollBar::trackColourId);
				}
				else
				{
					trackColour1 = thumbColour.overlaidWith(Colour(0x44000000));
					trackColour2 = thumbColour.overlaidWith(Colour(0x19000000));
				}

				g.setGradientFill(ColourGradient(trackColour1, gx1, gy1,
					trackColour2, gx2, gy2, false));
				// Cay doc
				g.fillPath(slotPath);

				if (isScrollbarVertical)
				{
					gx1 = x + width * 0.6f;
					gx2 = (float)x + width;
				}
				else
				{
					gy1 = y + height * 0.6f;
					gy2 = (float)y + height;
				}

				g.setGradientFill(ColourGradient(Colours::transparentBlack, gx1, gy1,
					Colour(0x19000000), gx2, gy2, false));

				//Cay doc
				g.fillPath(slotPath);

				g.setColour(thumbColour);
				g.fillPath(thumbPath);

				g.setGradientFill(ColourGradient(Colour(0x10000000), gx1, gy1,
					Colours::transparentBlack, gx2, gy2, false));

				g.saveState();

				if (isScrollbarVertical)
					g.reduceClipRegion(x + width / 2, y, width, height);
				else
					g.reduceClipRegion(x, y + height / 2, width, height);

				g.fillPath(thumbPath);
				g.restoreState();

				g.setColour(Colour(0x4c000000));
				g.strokePath(thumbPath, PathStrokeType(0.4f));
			};

			int getDefaultScrollbarWidth() override
			{
				return 5;
			}
		};
	private:
		ScopedPointer<LookAndFeelMethod> mVScrollBarLook;
	public:
		CustomListBox() :ListBox() {
			this->setColour(ListBox::ColourIds::backgroundColourId, Colour::fromFloatRGBA(0, 0, 0, 0));
			mVScrollBarLook = new LookAndFeelMethod();
			ScrollBar * scrollBar = this->getVerticalScrollBar();
			scrollBar->setLookAndFeel(mVScrollBarLook);
		};
		~CustomListBox() {
			mVScrollBarLook = nullptr;
		};
	};

	class Listener {
	public:
		virtual void selectedRowsChanged(ListBoxComponent *source, int lastRowSelected) = 0;
		virtual void listBoxItemClicked(ListBoxComponent *source, int row, const MouseEvent& e) = 0;
		virtual void listBoxItemDoubleClicked(ListBoxComponent *source, int row, const MouseEvent& e) = 0;
	};

	void addListBoxListener(Listener *listener) {
		mListeners.add(listener);
	};

	void removeListBoxListener(Listener *listener) {
		for (int i = 0; i < mListeners.size(); i++) {
			if (mListeners.getUnchecked(i) == listener) {
				mListeners.remove(i);
				break;
			}
		}
	};

	void removeAllListBoxListener() {
		mListeners.clear(false);
	}
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;

    // Binary resources:
    static const char* pluginmanager_checkbox_empty_button_png;
    static const int pluginmanager_checkbox_empty_button_pngSize;
    static const char* pluginmanager_checkbox_greyfill_button_png;
    static const int pluginmanager_checkbox_greyfill_button_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ScopedPointer<StringModel> mData;
	ScopedPointer<StringCheckBoxModel> mCheckBoxData;
	ScopedPointer<PluginCheckBoxModel> mPluginCheckBoxData;
	HeaderComponent* mHeaderCheckBox;
	ModelType mCheckList;
	Array<String> &mListStrings;
	OwnedArray<Listener> mListeners;

	// Some Private function
	void selectedRowsChanged(ListBoxComponent *source, int lastRowSelected) {
		for (int i = 0; i < mListeners.size(); i++) {
			mListeners.getUnchecked(i)->selectedRowsChanged(source, lastRowSelected);
		}
	};
	void listBoxItemClicked(ListBoxComponent *source, int row, const MouseEvent& e) {
		for (int i = 0; i < mListeners.size(); i++) {
			mListeners.getUnchecked(i)->listBoxItemClicked(source, row, e);
		}
	};
	void listBoxItemDoubleClicked(ListBoxComponent *source, int row, const MouseEvent& e) {
		for (int i = 0; i < mListeners.size(); i++) {
			mListeners.getUnchecked(i)->listBoxItemDoubleClicked(source, row, e);
		}
	};
	friend class StringModel;
	friend class StringCheckBoxModel;
	friend class PluginCheckBoxModel;

	static Array<String> sListStrings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<CustomListBox> listBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListBoxComponent)
};

//[EndFile] You can add extra defines here...
typedef ListBoxComponent::Listener ListBoxListener;
typedef ListBoxComponent::ModelType ListBoxModel;
//[/EndFile]

#endif   // __JUCE_HEADER_937F5D56504737B0__
