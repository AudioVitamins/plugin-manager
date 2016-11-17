{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf470
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red0\green116\blue0;\red170\green13\blue145;\red63\green110\blue116;
\red38\green71\blue75;\red28\green0\blue207;\red100\green56\blue32;\red196\green26\blue22;\red92\green38\blue153;
}
\paperw11900\paperh16840\margl1440\margr1440\vieww33400\viewh18740\viewkind0
\deftab529
\pard\tx529\pardeftab529\pardirnatural\partightenfactor0

\f0\fs22 \cf2 \CocoaLigature0 /*\
  ==============================================================================\
\
   This file is part of the JUCE library.\
   Copyright (c) 2015 - ROLI Ltd.\
\
   Permission is granted to use this software under the terms of either:\
   a) the GPL v2 (or any later version)\
   b) the Affero GPL v3\
\
   Details of these licenses can be found at: www.gnu.org/licenses\
\
   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY\
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR\
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\
\
   ------------------------------------------------------------------------------\
\
   To release a closed-source product which uses JUCE, commercial licenses are\
   available: visit www.juce.com for more information.\
\
  ==============================================================================\
*/\cf0 \
\
\cf3 class\cf0  \cf4 PluginListComponent\cf0 ::TableModel  : \cf3 public\cf0  \cf4 TableListBoxModel\cf0 \
\{\
\cf3 public\cf0 :\
    TableModel (\cf4 PluginListComponent\cf0 & c, \cf4 KnownPluginList\cf0 & l)  : \cf4 owner\cf0  (c), \cf4 list\cf0  (l) \{\}\
\
    \cf3 int\cf0  getNumRows() \cf3 override\cf0 \
    \{\
        \cf3 return\cf0  \cf4 list\cf0 .\cf5 getNumTypes\cf0 () + \cf4 list\cf0 .\cf5 getBlacklistedFiles\cf0 ().\cf5 size\cf0 ();\
    \}\
\
    \cf3 void\cf0  paintRowBackground (\cf4 Graphics\cf0 & g, \cf3 int\cf0  \cf2 /*rowNumber*/\cf0 , \cf3 int\cf0  \cf2 /*width*/\cf0 , \cf3 int\cf0  \cf2 /*height*/\cf0 , \cf3 bool\cf0  rowIsSelected) \cf3 override\cf0 \
    \{\
        \cf3 if\cf0  (rowIsSelected)\
            g.\cf5 fillAll\cf0  (\cf4 owner\cf0 .\cf5 findColour\cf0  (\cf4 TextEditor\cf0 ::\cf5 highlightColourId\cf0 ));\
    \}\
\
    \cf3 enum\cf0 \
    \{\
        nameCol = \cf6 1\cf0 ,\
        manufacturerCol = \cf6 2\cf0 ,\
        typeCol = \cf6 3\cf0 ,\
        descCol = \cf6 4\cf0 \
    \};\
\
    \cf3 void\cf0  paintCell (\cf4 Graphics\cf0 & g, \cf3 int\cf0  row, \cf3 int\cf0  columnId, \cf3 int\cf0  width, \cf3 int\cf0  height, \cf3 bool\cf0  \cf2 /*rowIsSelected*/\cf0 ) \cf3 override\cf0 \
    \{\
        \cf4 String\cf0  text;\
        \cf3 bool\cf0  isBlacklisted = row >= \cf4 list\cf0 .\cf5 getNumTypes\cf0 ();\
\
        \cf3 if\cf0  (isBlacklisted)\
        \{\
            \cf3 if\cf0  (columnId == \cf5 nameCol\cf0 )\
                text = \cf4 list\cf0 .\cf5 getBlacklistedFiles\cf0 () [\cf5 row\cf0  - \cf5 list\cf0 .\cf5 getNumTypes\cf0 ()];\
            \cf3 else\cf0  \cf3 if\cf0  (columnId == \cf5 descCol\cf0 )\
                text = \cf7 TRANS\cf0 (\cf8 "Deactivated after failing to initialise correctly"\cf0 );\
        \}\
        \cf3 else\cf0  \cf3 if\cf0  (\cf3 const\cf0  \cf4 PluginDescription\cf0 * \cf3 const\cf0  desc = \cf4 list\cf0 .\cf5 getType\cf0  (row))\
        \{\
            \cf3 switch\cf0  (columnId)\
            \{\
                \cf3 case\cf0  \cf5 nameCol\cf0 :         text = desc->\cf4 name\cf0 ; \cf3 break\cf0 ;\
                \cf3 case\cf0  \cf5 manufacturerCol\cf0 : text = desc->\cf4 manufacturerName\cf0 ; \cf3 break\cf0 ;\
                \cf3 case\cf0  \cf5 typeCol\cf0 :         text = desc->\cf4 pluginFormatName\cf0 ; \cf3 break\cf0 ;\
                \cf3 case\cf0  \cf5 descCol\cf0 :         text = \cf5 getPluginDescription\cf0  (*desc); \cf3 break\cf0 ;\
\
                \cf3 default\cf0 : \cf7 jassertfalse\cf0 ; \cf3 break\cf0 ;\
            \}\
        \}\
\
        \cf3 if\cf0  (text.\cf5 isNotEmpty\cf0 ())\
        \{\
            g.\cf5 setColour\cf0  (isBlacklisted ? \cf4 Colours\cf0 ::\cf4 red\cf0 \
                                       : columnId == \cf5 nameCol\cf0  ? \cf4 Colours\cf0 ::\cf4 white\cf0 \
                                                             : \cf4 Colours\cf0 ::\cf4 lightgrey\cf0 );\
            g.\cf5 setFont\cf0  (\cf4 Font\cf0  (height * \cf6 0.7f\cf0 , \cf4 Font\cf0 ::\cf5 bold\cf0 ));\
            g.\cf5 drawFittedText\cf0  (text, \cf6 4\cf0 , \cf6 0\cf0 , width - \cf6 6\cf0 , height, \cf4 Justification\cf0 ::\cf5 centredLeft\cf0 , \cf6 1\cf0 , \cf6 0.9f\cf0 );\
        \}\
    \}\
\
    \cf3 void\cf0  deleteKeyPressed (\cf3 int\cf0 ) \cf3 override\cf0 \
    \{\
        \cf4 owner\cf0 .\cf5 removeSelectedPlugins\cf0 ();\
    \}\
\
    \cf3 void\cf0  sortOrderChanged (\cf3 int\cf0  newSortColumnId, \cf3 bool\cf0  isForwards) \cf3 override\cf0 \
    \{\
        \cf3 switch\cf0  (newSortColumnId)\
        \{\
            \cf3 case\cf0  \cf5 nameCol\cf0 :         \cf4 list\cf0 .\cf5 sort\cf0  (\cf4 KnownPluginList\cf0 ::\cf5 sortAlphabetically\cf0 , isForwards); \cf3 break\cf0 ;\
            \cf3 case\cf0  \cf5 typeCol\cf0 :         \cf4 list\cf0 .\cf5 sort\cf0  (\cf4 KnownPluginList\cf0 ::\cf5 sortByFormat\cf0 , isForwards); \cf3 break\cf0 ;\
            \cf3 case\cf0  \cf5 manufacturerCol\cf0 : \cf4 list\cf0 .\cf5 sort\cf0  (\cf4 KnownPluginList\cf0 ::\cf5 sortByManufacturer\cf0 , isForwards); \cf3 break\cf0 ;\
            \cf3 case\cf0  \cf5 descCol\cf0 :         \cf3 break\cf0 ;\
\
            \cf3 default\cf0 : \cf7 jassertfalse\cf0 ; \cf3 break\cf0 ;\
        \}\
    \}\
\
    \cf3 static\cf0  \cf4 String\cf0  getPluginDescription (\cf3 const\cf0  \cf4 PluginDescription\cf0 & desc)\
    \{\
        \cf4 StringArray\cf0  items;\
\
        \cf3 if\cf0  (desc.\cf4 descriptiveName\cf0  != desc.\cf4 name\cf0 )\
            items.\cf5 add\cf0  (desc.\cf4 descriptiveName\cf0 );\
\
        items.\cf5 add\cf0  (desc.\cf4 version\cf0 );\
\
        items.\cf5 removeEmptyStrings\cf0 ();\
        \cf3 return\cf0  items.\cf5 joinIntoString\cf0  (\cf8 " - "\cf0 );\
    \}\
\
    \cf4 PluginListComponent\cf0 & owner;\
    \cf4 KnownPluginList\cf0 & list;\
\
    \cf7 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR\cf0  (\cf4 TableModel\cf0 )\
\};\
\
\cf2 //==============================================================================\cf0 \
\cf4 PluginListComponent\cf0 ::PluginListComponent (\cf4 AudioPluginFormatManager\cf0 & manager, \cf4 KnownPluginList\cf0 & listToEdit,\
                                          \cf3 const\cf0  \cf4 File\cf0 & deadMansPedal, \cf4 PropertiesFile\cf0 * \cf3 const\cf0  props,\
                                          \cf3 bool\cf0  allowPluginsWhichRequireAsynchronousInstantiation)\
    : \cf4 formatManager\cf0  (manager),\
      \cf4 list\cf0  (listToEdit),\
      \cf4 deadMansPedalFile\cf0  (deadMansPedal),\
      \cf4 optionsButton\cf0  (\cf8 "Options..."\cf0 ),\
      \cf4 propertiesToUse\cf0  (props),\
      \cf4 allowAsync\cf0  (allowPluginsWhichRequireAsynchronousInstantiation),\
      \cf4 numThreads\cf0  (\cf4 allowAsync\cf0  ? \cf6 1\cf0  : \cf6 0\cf0 )\
\{\
    \cf4 tableModel\cf0  = \cf3 new\cf0  \cf4 TableModel\cf0  (*\cf3 this\cf0 , listToEdit);\
\
    \cf4 TableHeaderComponent\cf0 & header = \cf4 table\cf0 .\cf5 getHeader\cf0 ();\
\
    header.\cf5 addColumn\cf0  (\cf7 TRANS\cf0 (\cf8 "Name"\cf0 ),         \cf4 TableModel\cf0 ::\cf5 nameCol\cf0 ,         \cf6 200\cf0 , \cf6 100\cf0 , \cf6 700\cf0 , \cf4 TableHeaderComponent\cf0 ::\cf5 defaultFlags\cf0  | \cf4 TableHeaderComponent\cf0 ::\cf5 sortedForwards\cf0 );\
    header.\cf5 addColumn\cf0  (\cf7 TRANS\cf0 (\cf8 "Manufacturer"\cf0 ), \cf4 TableModel\cf0 ::\cf5 manufacturerCol\cf0 , \cf6 200\cf0 , \cf6 100\cf0 , \cf6 300\cf0 );\
    header.\cf5 addColumn\cf0  (\cf7 TRANS\cf0 (\cf8 "Format"\cf0 ),       \cf4 TableModel\cf0 ::\cf5 typeCol\cf0 ,         \cf6 80\cf0 , \cf6 80\cf0 , \cf6 80\cf0 ,    \cf4 TableHeaderComponent\cf0 ::\cf5 notResizable\cf0 );\
    header.\cf5 addColumn\cf0  (\cf7 TRANS\cf0 (\cf8 "Description"\cf0 ),  \cf4 TableModel\cf0 ::\cf5 descCol\cf0 ,         \cf6 300\cf0 , \cf6 100\cf0 , \cf6 500\cf0 , \cf4 TableHeaderComponent\cf0 ::\cf5 notSortable\cf0 );\
\
    \cf4 table\cf0 .\cf5 setHeaderHeight\cf0  (\cf6 22\cf0 );\
    \cf4 table\cf0 .\cf5 setRowHeight\cf0  (\cf6 20\cf0 );\
    \cf4 table\cf0 .\cf5 setModel\cf0  (\cf4 tableModel\cf0 );\
    \cf4 table\cf0 .\cf5 setMultipleSelectionEnabled\cf0  (\cf3 true\cf0 );\
    \cf5 addAndMakeVisible\cf0  (\cf4 table\cf0 );\
\
    \cf5 addAndMakeVisible\cf0  (\cf4 optionsButton\cf0 );\
    \cf4 optionsButton\cf0 .\cf5 addListener\cf0  (\cf3 this\cf0 );\
    \cf4 optionsButton\cf0 .\cf5 setTriggeredOnMouseDown\cf0  (\cf3 true\cf0 );\
\
    \cf5 setSize\cf0  (\cf6 400\cf0 , \cf6 600\cf0 );\
    \cf4 list\cf0 .\cf5 addChangeListener\cf0  (\cf3 this\cf0 );\
    \cf5 updateList\cf0 ();\
    \cf4 table\cf0 .\cf5 getHeader\cf0 ().\cf5 reSortTable\cf0 ();\
\
    \cf4 PluginDirectoryScanner\cf0 ::\cf5 applyBlacklistingsFromDeadMansPedal\cf0  (\cf4 list\cf0 , \cf4 deadMansPedalFile\cf0 );\
    \cf4 deadMansPedalFile\cf0 .\cf5 deleteFile\cf0 ();\
\}\
\
\cf4 PluginListComponent\cf0 ::~PluginListComponent()\
\{\
    \cf4 list\cf0 .\cf5 removeChangeListener\cf0  (\cf3 this\cf0 );\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::setOptionsButtonText (\cf3 const\cf0  \cf4 String\cf0 & newText)\
\{\
    \cf4 optionsButton\cf0 .\cf5 setButtonText\cf0  (newText);\
    \cf5 resized\cf0 ();\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::setScanDialogText (\cf3 const\cf0  \cf4 String\cf0 & title, \cf3 const\cf0  \cf4 String\cf0 & content)\
\{\
    \cf4 dialogTitle\cf0  = title;\
    \cf4 dialogText\cf0  = content;\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::setNumberOfThreadsForScanning (\cf3 int\cf0  num)\
\{\
    \cf4 numThreads\cf0  = num;\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::resized()\
\{\
    \cf9 Rectangle\cf0 <\cf3 int\cf0 > r (\cf5 getLocalBounds\cf0 ().\cf5 reduced\cf0  (\cf6 2\cf0 ));\
\
    \cf4 optionsButton\cf0 .\cf5 setBounds\cf0  (r.\cf5 removeFromBottom\cf0  (\cf6 24\cf0 ));\
    \cf4 optionsButton\cf0 .\cf5 changeWidthToFitText\cf0  (\cf6 24\cf0 );\
\
    r.\cf5 removeFromBottom\cf0  (\cf6 3\cf0 );\
    \cf4 table\cf0 .\cf5 setBounds\cf0  (r);\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::changeListenerCallback (\cf4 ChangeBroadcaster\cf0 *)\
\{\
    \cf4 table\cf0 .\cf5 getHeader\cf0 ().\cf5 reSortTable\cf0 ();\
    \cf5 updateList\cf0 ();\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::updateList()\
\{\
    \cf4 table\cf0 .\cf5 updateContent\cf0 ();\
    \cf4 table\cf0 .\cf5 repaint\cf0 ();\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::removeSelectedPlugins()\
\{\
    \cf3 const\cf0  \cf4 SparseSet\cf0 <\cf3 int\cf0 > selected (\cf4 table\cf0 .\cf5 getSelectedRows\cf0 ());\
\
    \cf3 for\cf0  (\cf3 int\cf0  i = \cf4 table\cf0 .\cf5 getNumRows\cf0 (); --i >= \cf6 0\cf0 ;)\
        \cf3 if\cf0  (selected.\cf5 contains\cf0  (i))\
            \cf5 removePluginItem\cf0  (i);\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::setTableModel (\cf4 TableListBoxModel\cf0 * model)\
\{\
    \cf4 table\cf0 .\cf5 setModel\cf0  (\cf3 nullptr\cf0 );\
    \cf4 tableModel\cf0  = model;\
    \cf4 table\cf0 .\cf5 setModel\cf0  (\cf4 tableModel\cf0 );\
\
    \cf4 table\cf0 .\cf5 getHeader\cf0 ().\cf5 reSortTable\cf0 ();\
    \cf4 table\cf0 .\cf5 updateContent\cf0 ();\
    \cf4 table\cf0 .\cf5 repaint\cf0 ();\
\}\
\
\cf3 bool\cf0  \cf4 PluginListComponent\cf0 ::canShowSelectedFolder() \cf3 const\cf0 \
\{\
    \cf3 if\cf0  (\cf3 const\cf0  \cf4 PluginDescription\cf0 * \cf3 const\cf0  desc = \cf4 list\cf0 .\cf5 getType\cf0  (\cf4 table\cf0 .\cf5 getSelectedRow\cf0 ()))\
        \cf3 return\cf0  \cf4 File\cf0 ::\cf5 createFileWithoutCheckingPath\cf0  (desc->\cf4 fileOrIdentifier\cf0 ).\cf5 exists\cf0 ();\
\
    \cf3 return\cf0  \cf3 false\cf0 ;\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::showSelectedFolder()\
\{\
    \cf3 if\cf0  (\cf5 canShowSelectedFolder\cf0 ())\
        \cf3 if\cf0  (\cf3 const\cf0  \cf4 PluginDescription\cf0 * \cf3 const\cf0  desc = \cf4 list\cf0 .\cf5 getType\cf0  (\cf4 table\cf0 .\cf5 getSelectedRow\cf0 ()))\
            \cf4 File\cf0  (desc->\cf4 fileOrIdentifier\cf0 ).\cf5 getParentDirectory\cf0 ().\cf5 startAsProcess\cf0 ();\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::removeMissingPlugins()\
\{\
    \cf3 for\cf0  (\cf3 int\cf0  i = \cf4 list\cf0 .\cf5 getNumTypes\cf0 (); --i >= \cf6 0\cf0 ;)\
        \cf3 if\cf0  (! \cf4 formatManager\cf0 .\cf5 doesPluginStillExist\cf0  (*\cf4 list\cf0 .\cf5 getType\cf0  (i)))\
            \cf4 list\cf0 .\cf5 removeType\cf0  (i);\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::removePluginItem (\cf3 int\cf0  index)\
\{\
    \cf3 if\cf0  (index < \cf4 list\cf0 .\cf5 getNumTypes\cf0 ())\
        \cf4 list\cf0 .\cf5 removeType\cf0  (index);\
    \cf3 else\cf0 \
        \cf4 list\cf0 .\cf5 removeFromBlacklist\cf0  (\cf4 list\cf0 .\cf5 getBlacklistedFiles\cf0 () [\cf5 index\cf0  - \cf5 list\cf0 .\cf5 getNumTypes\cf0 ()]);\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::optionsMenuStaticCallback (\cf3 int\cf0  result, \cf4 PluginListComponent\cf0 * pluginList)\
\{\
    \cf3 if\cf0  (pluginList != \cf3 nullptr\cf0 )\
        pluginList->\cf5 optionsMenuCallback\cf0  (result);\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::optionsMenuCallback (\cf3 int\cf0  result)\
\{\
    \cf3 switch\cf0  (result)\
    \{\
        \cf3 case\cf0  \cf6 0\cf0 :   \cf3 break\cf0 ;\
        \cf3 case\cf0  \cf6 1\cf0 :   \cf4 list\cf0 .\cf5 clear\cf0 (); \cf3 break\cf0 ;\
        \cf3 case\cf0  \cf6 2\cf0 :   \cf5 removeSelectedPlugins\cf0 (); \cf3 break\cf0 ;\
        \cf3 case\cf0  \cf6 3\cf0 :   \cf5 showSelectedFolder\cf0 (); \cf3 break\cf0 ;\
        \cf3 case\cf0  \cf6 4\cf0 :   \cf5 removeMissingPlugins\cf0 (); \cf3 break\cf0 ;\
\
        \cf3 default\cf0 :\
            \cf3 if\cf0  (\cf4 AudioPluginFormat\cf0 * format = \cf4 formatManager\cf0 .\cf5 getFormat\cf0  (result - \cf6 10\cf0 ))\
                \cf5 scanFor\cf0  (*format);\
\
            \cf3 break\cf0 ;\
    \}\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::buttonClicked (\cf4 Button\cf0 * button)\
\{\
    \cf3 if\cf0  (button == &\cf4 optionsButton\cf0 )\
    \{\
        \cf4 PopupMenu\cf0  menu;\
        menu.\cf5 addItem\cf0  (\cf6 1\cf0 , \cf7 TRANS\cf0 (\cf8 "Clear list"\cf0 ));\
        menu.\cf5 addItem\cf0  (\cf6 2\cf0 , \cf7 TRANS\cf0 (\cf8 "Remove selected plug-in from list"\cf0 ), \cf4 table\cf0 .\cf5 getNumSelectedRows\cf0 () > \cf6 0\cf0 );\
        menu.\cf5 addItem\cf0  (\cf6 3\cf0 , \cf7 TRANS\cf0 (\cf8 "Show folder containing selected plug-in"\cf0 ), \cf5 canShowSelectedFolder\cf0 ());\
        menu.\cf5 addItem\cf0  (\cf6 4\cf0 , \cf7 TRANS\cf0 (\cf8 "Remove any plug-ins whose files no longer exist"\cf0 ));\
        menu.\cf5 addSeparator\cf0 ();\
\
        \cf3 for\cf0  (\cf3 int\cf0  i = \cf6 0\cf0 ; i < \cf4 formatManager\cf0 .\cf5 getNumFormats\cf0 (); ++i)\
        \{\
            \cf4 AudioPluginFormat\cf0 * \cf3 const\cf0  format = \cf4 formatManager\cf0 .\cf5 getFormat\cf0  (i);\
\
            \cf3 if\cf0  (format->\cf5 canScanForPlugins\cf0 ())\
                menu.\cf5 addItem\cf0  (\cf6 10\cf0  + i, \cf8 "Scan for new or updated "\cf0  + format->\cf5 getName\cf0 () + \cf8 " plug-ins"\cf0 );\
        \}\
\
        menu.\cf5 showMenuAsync\cf0  (\cf4 PopupMenu\cf0 ::\cf4 Options\cf0 ().\cf5 withTargetComponent\cf0  (&\cf4 optionsButton\cf0 ),\
                            \cf4 ModalCallbackFunction\cf0 ::\cf5 forComponent\cf0  (\cf5 optionsMenuStaticCallback\cf0 , \cf3 this\cf0 ));\
    \}\
\}\
\
\cf3 bool\cf0  \cf4 PluginListComponent\cf0 ::isInterestedInFileDrag (\cf3 const\cf0  \cf4 StringArray\cf0 & \cf2 /*files*/\cf0 )\
\{\
    \cf3 return\cf0  \cf3 true\cf0 ;\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::filesDropped (\cf3 const\cf0  \cf4 StringArray\cf0 & files, \cf3 int\cf0 , \cf3 int\cf0 )\
\{\
    \cf4 OwnedArray\cf0 <\cf4 PluginDescription\cf0 > typesFound;\
    \cf4 list\cf0 .\cf5 scanAndAddDragAndDroppedFiles\cf0  (\cf4 formatManager\cf0 , files, typesFound);\
\}\
\
\cf4 FileSearchPath\cf0  \cf4 PluginListComponent\cf0 ::getLastSearchPath (\cf4 PropertiesFile\cf0 & properties, \cf4 AudioPluginFormat\cf0 & format)\
\{\
    \cf3 return\cf0  \cf4 FileSearchPath\cf0  (properties.\cf5 getValue\cf0  (\cf8 "lastPluginScanPath_"\cf0  + format.\cf5 getName\cf0 (),\
                                                format.\cf5 getDefaultLocationsToSearch\cf0 ().\cf5 toString\cf0 ()));\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::setLastSearchPath (\cf4 PropertiesFile\cf0 & properties, \cf4 AudioPluginFormat\cf0 & format,\
                                             \cf3 const\cf0  \cf4 FileSearchPath\cf0 & newPath)\
\{\
    properties.\cf5 setValue\cf0  (\cf8 "lastPluginScanPath_"\cf0  + format.\cf5 getName\cf0 (), newPath.\cf5 toString\cf0 ());\
\}\
\
\cf2 //==============================================================================\cf0 \
\cf3 class\cf0  \cf4 PluginListComponent\cf0 ::Scanner    : \cf3 private\cf0  \cf4 Timer\cf0 \
\{\
\cf3 public\cf0 :\
    Scanner (\cf4 PluginListComponent\cf0 & plc, \cf4 AudioPluginFormat\cf0 & format, \cf4 PropertiesFile\cf0 * properties,\
             \cf3 bool\cf0  allowPluginsWhichRequireAsynchronousInstantiation, \cf3 int\cf0  threads,\
             \cf3 const\cf0  \cf4 String\cf0 & title, \cf3 const\cf0  \cf4 String\cf0 & text)\
        : \cf4 owner\cf0  (plc), \cf4 formatToScan\cf0  (format), \cf4 propertiesToUse\cf0  (properties),\
          \cf4 pathChooserWindow\cf0  (\cf7 TRANS\cf0 (\cf8 "Select folders to scan..."\cf0 ), \cf4 String\cf0 (), \cf4 AlertWindow\cf0 ::\cf5 NoIcon\cf0 ),\
          \cf4 progressWindow\cf0  (title, text, \cf4 AlertWindow\cf0 ::\cf5 NoIcon\cf0 ),\
          \cf4 progress\cf0  (\cf6 0.0\cf0 ), \cf4 numThreads\cf0  (threads), \cf4 allowAsync\cf0  (allowPluginsWhichRequireAsynchronousInstantiation),\
          \cf4 finished\cf0  (\cf3 false\cf0 )\
    \{\
        \cf4 FileSearchPath\cf0  path (\cf4 formatToScan\cf0 .\cf5 getDefaultLocationsToSearch\cf0 ());\
\
        \cf2 // You need to use at least one thread when scanning plug-ins asynchronously\cf0 \
        \cf7 jassert\cf0  (! \cf4 allowAsync\cf0  || (\cf4 numThreads\cf0  > \cf6 0\cf0 ));\
\
        \cf3 if\cf0  (path.\cf5 getNumPaths\cf0 () > \cf6 0\cf0 ) \cf2 // if the path is empty, then paths aren't used for this format.\cf0 \
        \{\
\cf7            #if ! JUCE_IOS\cf0 \
            \cf3 if\cf0  (\cf4 propertiesToUse\cf0  != \cf3 nullptr\cf0 )\
                path = \cf5 getLastSearchPath\cf0  (*\cf4 propertiesToUse\cf0 , \cf4 formatToScan\cf0 );\
\cf7            #endif\cf0 \
\
            \cf4 pathList\cf0 .\cf5 setSize\cf0  (\cf6 500\cf0 , \cf6 300\cf0 );\
            \cf4 pathList\cf0 .\cf5 setPath\cf0  (path);\
\
            \cf4 pathChooserWindow\cf0 .\cf5 addCustomComponent\cf0  (&\cf4 pathList\cf0 );\
            \cf4 pathChooserWindow\cf0 .\cf5 addButton\cf0  (\cf7 TRANS\cf0 (\cf8 "Scan"\cf0 ),   \cf6 1\cf0 , \cf4 KeyPress\cf0  (\cf4 KeyPress\cf0 ::\cf4 returnKey\cf0 ));\
            \cf4 pathChooserWindow\cf0 .\cf5 addButton\cf0  (\cf7 TRANS\cf0 (\cf8 "Cancel"\cf0 ), \cf6 0\cf0 , \cf4 KeyPress\cf0  (\cf4 KeyPress\cf0 ::\cf4 escapeKey\cf0 ));\
\
            \cf4 pathChooserWindow\cf0 .\cf5 enterModalState\cf0  (\cf3 true\cf0 ,\
                                               \cf4 ModalCallbackFunction\cf0 ::\cf5 forComponent\cf0  (\cf5 startScanCallback\cf0 ,\
                                                                                    &\cf4 pathChooserWindow\cf0 , \cf3 this\cf0 ),\
                                               \cf3 false\cf0 );\
        \}\
        \cf3 else\cf0 \
        \{\
            \cf5 startScan\cf0 ();\
        \}\
    \}\
\
    ~Scanner()\
    \{\
        \cf3 if\cf0  (\cf4 pool\cf0  != \cf3 nullptr\cf0 )\
        \{\
            \cf4 pool\cf0 ->\cf5 removeAllJobs\cf0  (\cf3 true\cf0 , \cf6 60000\cf0 );\
            \cf4 pool\cf0  = \cf3 nullptr\cf0 ;\
        \}\
    \}\
\
\cf3 private\cf0 :\
    \cf4 PluginListComponent\cf0 & owner;\
    \cf4 AudioPluginFormat\cf0 & formatToScan;\
    \cf4 PropertiesFile\cf0 * propertiesToUse;\
    \cf4 ScopedPointer\cf0 <\cf4 PluginDirectoryScanner\cf0 > scanner;\
    \cf4 AlertWindow\cf0  pathChooserWindow, progressWindow;\
    \cf4 FileSearchPathListComponent\cf0  pathList;\
    \cf4 String\cf0  pluginBeingScanned;\
    \cf3 double\cf0  progress;\
    \cf3 int\cf0  numThreads;\
    \cf3 bool\cf0  allowAsync, finished;\
    \cf4 ScopedPointer\cf0 <\cf4 ThreadPool\cf0 > pool;\
\
    \cf3 static\cf0  \cf3 void\cf0  startScanCallback (\cf3 int\cf0  result, \cf4 AlertWindow\cf0 * alert, \cf4 Scanner\cf0 * scanner)\
    \{\
        \cf3 if\cf0  (alert != \cf3 nullptr\cf0  && scanner != \cf3 nullptr\cf0 )\
        \{\
            \cf3 if\cf0  (result != \cf6 0\cf0 )\
                scanner->\cf5 warnUserAboutStupidPaths\cf0 ();\
            \cf3 else\cf0 \
                scanner->\cf5 finishedScan\cf0 ();\
        \}\
    \}\
\
    \cf2 // Try to dissuade people from to scanning their entire C: drive, or other system folders.\cf0 \
    \cf3 void\cf0  warnUserAboutStupidPaths()\
    \{\
        \cf3 for\cf0  (\cf3 int\cf0  i = \cf6 0\cf0 ; i < \cf4 pathList\cf0 .\cf5 getPath\cf0 ().\cf5 getNumPaths\cf0 (); ++i)\
        \{\
            \cf3 const\cf0  \cf4 File\cf0  f (\cf4 pathList\cf0 .\cf5 getPath\cf0 ()[\cf5 i\cf0 ]);\
\
            \cf3 if\cf0  (\cf5 isStupidPath\cf0  (f))\
            \{\
                \cf4 AlertWindow\cf0 ::\cf5 showOkCancelBox\cf0  (\cf4 AlertWindow\cf0 ::\cf5 WarningIcon\cf0 ,\
                                              \cf7 TRANS\cf0 (\cf8 "Plugin Scanning"\cf0 ),\
                                              \cf7 TRANS\cf0 (\cf8 "If you choose to scan folders that contain non-plugin files, "\cf0 \
                                                    \cf8 "then scanning may take a long time, and can cause crashes when "\cf0 \
                                                    \cf8 "attempting to load unsuitable files."\cf0 )\
                                                + \cf4 newLine\cf0 \
                                                + \cf7 TRANS\cf0  (\cf8 "Are you sure you want to scan the folder \\"XYZ\\"?"\cf0 )\
                                                   .\cf5 replace\cf0  (\cf8 "XYZ"\cf0 , f.\cf5 getFullPathName\cf0 ()),\
                                              \cf7 TRANS\cf0  (\cf8 "Scan"\cf0 ),\
                                              \cf4 String\cf0 (),\
                                              \cf3 nullptr\cf0 ,\
                                              \cf4 ModalCallbackFunction\cf0 ::\cf5 create\cf0  (\cf5 warnAboutStupidPathsCallback\cf0 , \cf3 this\cf0 ));\
                \cf3 return\cf0 ;\
            \}\
        \}\
\
        \cf5 startScan\cf0 ();\
    \}\
\
    \cf3 static\cf0  \cf3 bool\cf0  isStupidPath (\cf3 const\cf0  \cf4 File\cf0 & f)\
    \{\
        \cf4 Array\cf0 <\cf4 File\cf0 > roots;\
        \cf4 File\cf0 ::\cf5 findFileSystemRoots\cf0  (roots);\
\
        \cf3 if\cf0  (roots.\cf5 contains\cf0  (f))\
            \cf3 return\cf0  \cf3 true\cf0 ;\
\
        \cf4 File\cf0 ::\cf4 SpecialLocationType\cf0  pathsThatWouldBeStupidToScan[]\
            = \{ \cf4 File\cf0 ::\cf5 globalApplicationsDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 userHomeDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 userDocumentsDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 userDesktopDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 tempDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 userMusicDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 userMoviesDirectory\cf0 ,\
                \cf4 File\cf0 ::\cf5 userPicturesDirectory\cf0  \};\
\
        \cf3 for\cf0  (\cf3 int\cf0  i = \cf6 0\cf0 ; i < \cf5 numElementsInArray\cf0  (pathsThatWouldBeStupidToScan); ++i)\
        \{\
            \cf3 const\cf0  \cf4 File\cf0  sillyFolder (\cf4 File\cf0 ::\cf5 getSpecialLocation\cf0  (pathsThatWouldBeStupidToScan[i]));\
\
            \cf3 if\cf0  (f == sillyFolder || sillyFolder.\cf5 isAChildOf\cf0  (f))\
                \cf3 return\cf0  \cf3 true\cf0 ;\
        \}\
\
        \cf3 return\cf0  \cf3 false\cf0 ;\
    \}\
\
    \cf3 static\cf0  \cf3 void\cf0  warnAboutStupidPathsCallback (\cf3 int\cf0  result, \cf4 Scanner\cf0 * scanner)\
    \{\
        \cf3 if\cf0  (result != \cf6 0\cf0 )\
            scanner->\cf5 startScan\cf0 ();\
        \cf3 else\cf0 \
            scanner->\cf5 finishedScan\cf0 ();\
    \}\
\
    \cf3 void\cf0  startScan()\
    \{\
        \cf4 pathChooserWindow\cf0 .\cf5 setVisible\cf0  (\cf3 false\cf0 );\
\
        \cf4 scanner\cf0  = \cf3 new\cf0  \cf4 PluginDirectoryScanner\cf0  (\cf4 owner\cf0 .\cf4 list\cf0 , \cf4 formatToScan\cf0 , \cf4 pathList\cf0 .\cf5 getPath\cf0 (),\
                                              \cf3 true\cf0 , \cf4 owner\cf0 .\cf4 deadMansPedalFile\cf0 , \cf4 allowAsync\cf0 );\
\
        \cf3 if\cf0  (\cf4 propertiesToUse\cf0  != \cf3 nullptr\cf0 )\
        \{\
            \cf5 setLastSearchPath\cf0  (*\cf4 propertiesToUse\cf0 , \cf4 formatToScan\cf0 , \cf4 pathList\cf0 .\cf5 getPath\cf0 ());\
            \cf4 propertiesToUse\cf0 ->\cf5 saveIfNeeded\cf0 ();\
        \}\
\
        \cf4 progressWindow\cf0 .\cf5 addButton\cf0  (\cf7 TRANS\cf0 (\cf8 "Cancel"\cf0 ), \cf6 0\cf0 , \cf4 KeyPress\cf0  (\cf4 KeyPress\cf0 ::\cf4 escapeKey\cf0 ));\
        \cf4 progressWindow\cf0 .\cf5 addProgressBarComponent\cf0  (\cf4 progress\cf0 );\
        \cf4 progressWindow\cf0 .\cf5 enterModalState\cf0 ();\
\
        \cf3 if\cf0  (\cf4 numThreads\cf0  > \cf6 0\cf0 )\
        \{\
            \cf4 pool\cf0  = \cf3 new\cf0  \cf4 ThreadPool\cf0  (\cf4 numThreads\cf0 );\
\
            \cf3 for\cf0  (\cf3 int\cf0  i = \cf4 numThreads\cf0 ; --i >= \cf6 0\cf0 ;)\
                \cf4 pool\cf0 ->\cf5 addJob\cf0  (\cf3 new\cf0  \cf4 ScanJob\cf0  (*\cf3 this\cf0 ), \cf3 true\cf0 );\
        \}\
\
        \cf5 startTimer\cf0  (\cf6 20\cf0 );\
    \}\
\
    \cf3 void\cf0  finishedScan()\
    \{\
        \cf4 owner\cf0 .\cf5 scanFinished\cf0  (\cf4 scanner\cf0  != \cf3 nullptr\cf0  ? \cf4 scanner\cf0 ->\cf5 getFailedFiles\cf0 ()\
                                               : \cf4 StringArray\cf0 ());\
    \}\
\
    \cf3 void\cf0  timerCallback() \cf3 override\cf0 \
    \{\
        \cf3 if\cf0  (\cf4 pool\cf0  == \cf3 nullptr\cf0 )\
        \{\
            \cf3 if\cf0  (\cf5 doNextScan\cf0 ())\
                \cf5 startTimer\cf0  (\cf6 20\cf0 );\
        \}\
\
        \cf3 if\cf0  (! \cf4 progressWindow\cf0 .\cf5 isCurrentlyModal\cf0 ())\
            \cf4 finished\cf0  = \cf3 true\cf0 ;\
\
        \cf3 if\cf0  (\cf4 finished\cf0 )\
            \cf5 finishedScan\cf0 ();\
        \cf3 else\cf0 \
            \cf4 progressWindow\cf0 .\cf5 setMessage\cf0  (\cf7 TRANS\cf0 (\cf8 "Testing"\cf0 ) + \cf8 ":\\n\\n"\cf0  + \cf4 pluginBeingScanned\cf0 );\
    \}\
\
    \cf3 bool\cf0  doNextScan()\
    \{\
        \cf3 if\cf0  (\cf4 scanner\cf0 ->\cf5 scanNextFile\cf0  (\cf3 true\cf0 , \cf4 pluginBeingScanned\cf0 ))\
        \{\
            \cf4 progress\cf0  = \cf4 scanner\cf0 ->\cf5 getProgress\cf0 ();\
            \cf3 return\cf0  \cf3 true\cf0 ;\
        \}\
\
        \cf4 finished\cf0  = \cf3 true\cf0 ;\
        \cf3 return\cf0  \cf3 false\cf0 ;\
    \}\
\
    \cf3 struct\cf0  ScanJob  : \cf3 public\cf0  \cf4 ThreadPoolJob\cf0 \
    \{\
        ScanJob (\cf4 Scanner\cf0 & s)  : \cf4 ThreadPoolJob\cf0  (\cf8 "pluginscan"\cf0 ), \cf4 scanner\cf0  (s) \{\}\
\
        \cf4 JobStatus\cf0  runJob()\
        \{\
            \cf3 while\cf0  (\cf4 scanner\cf0 .\cf5 doNextScan\cf0 () && ! \cf5 shouldExit\cf0 ())\
            \{\}\
\
            \cf3 return\cf0  \cf5 jobHasFinished\cf0 ;\
        \}\
\
        \cf4 Scanner\cf0 & scanner;\
\
        \cf7 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR\cf0  (\cf4 ScanJob\cf0 )\
    \};\
\
    \cf7 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR\cf0  (\cf4 Scanner\cf0 )\
\};\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::scanFor (\cf4 AudioPluginFormat\cf0 & format)\
\{\
    \cf4 currentScanner\cf0  = \cf3 new\cf0  \cf4 Scanner\cf0  (*\cf3 this\cf0 , format, \cf4 propertiesToUse\cf0 , \cf4 allowAsync\cf0 , \cf4 numThreads\cf0 ,\
                                  \cf4 dialogTitle\cf0 .\cf5 isNotEmpty\cf0 () ? \cf4 dialogTitle\cf0  : \cf7 TRANS\cf0 (\cf8 "Scanning for plug-ins..."\cf0 ),\
                                  \cf4 dialogText\cf0 .\cf5 isNotEmpty\cf0 ()  ? \cf4 dialogText\cf0   : \cf7 TRANS\cf0 (\cf8 "Searching for all possible plug-in files..."\cf0 ));\
\}\
\
\cf3 bool\cf0  \cf4 PluginListComponent\cf0 ::isScanning() \cf3 const\cf0  \cf3 noexcept\cf0 \
\{\
    \cf3 return\cf0  \cf4 currentScanner\cf0  != \cf3 nullptr\cf0 ;\
\}\
\
\cf3 void\cf0  \cf4 PluginListComponent\cf0 ::scanFinished (\cf3 const\cf0  \cf4 StringArray\cf0 & failedFiles)\
\{\
    \cf4 StringArray\cf0  shortNames;\
\
    \cf3 for\cf0  (\cf3 int\cf0  i = \cf6 0\cf0 ; i < failedFiles.\cf5 size\cf0 (); ++i)\
        shortNames.\cf5 add\cf0  (\cf4 File\cf0 ::\cf5 createFileWithoutCheckingPath\cf0  (failedFiles[\cf5 i\cf0 ]).\cf5 getFileName\cf0 ());\
\
    \cf4 currentScanner\cf0  = \cf3 nullptr\cf0 ; \cf2 // mustn't delete this before using the failed files array\cf0 \
\
    \cf3 if\cf0  (shortNames.\cf5 size\cf0 () > \cf6 0\cf0 )\
        \cf4 AlertWindow\cf0 ::\cf5 showMessageBoxAsync\cf0  (\cf4 AlertWindow\cf0 ::\cf5 InfoIcon\cf0 ,\
                                          \cf7 TRANS\cf0 (\cf8 "Scan complete"\cf0 ),\
                                          \cf7 TRANS\cf0 (\cf8 "Note that the following files appeared to be plugin files, but failed to load correctly"\cf0 )\
                                            + \cf8 ":\\n\\n"\cf0 \
                                            + shortNames.\cf5 joinIntoString\cf0  (\cf8 ", "\cf0 ));\
\}\
}