/*
  ==============================================================================

    XmlUtil.h
    Created: 17 Dec 2016 11:38:18pm
    Author:  hungc

  ==============================================================================
*/

#ifndef XMLUTIL_H_INCLUDED
#define XMLUTIL_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"

class XmlUtil {
public:
	static XmlElement *ToXml(SparseSet<int> val) {
		XmlElement* const e = new XmlElement("SparseSetInt");
		for (int i = 0; i < val.size(); ++i) {
			e->createNewChildElement("Data")->setAttribute("Val", val[i]);
		}
		return e;
	};
	static SparseSet<int> FromXml(XmlElement * xml) {
		SparseSet<int> val;
		if (xml->hasTagName("SparseSetInt")) {
			forEachXmlChildElementWithTagName(*xml, e, "Data") {
				int set = e->getIntAttribute("Val");
				val.addRange(Range <int>(set,set + 1));
			}
		}
		return val;
	};
};




#endif  // XMLUTIL_H_INCLUDED
