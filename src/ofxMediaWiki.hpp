//
//  ofxMediaWiki.hpp
//  ofxwiki
//
//  Created by YOKOYAMA Toru on 2016/06/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxTextWriter.h"
#include "ofxOsc.h"

class ofxMediaWiki
{
    
public:
    
    ofxMediaWiki();
    ~ofxMediaWiki();
    
    void newResponse(ofxHttpResponse & response);

    void setup(string postURL, int PORT);
    void setup(string postURL, int PORT, string fontName, int fontSize);
    void oscUpdateMessage(string oscAddress);
    void TextUpdatePosition(float slideSpeed);
    void drawTextAnimation(float setLineHeight, int margin_x, int margin_y);
    
    void textRender(string texts,int textSpeed, int stringColumn);
    
    void eraseOneChar(string removeText);
    void eraseOneTwoChar(string removeText);
    void eraseHeaderTexts(string removeTexts);
    void eraseTwoCharAfterAll(string removeTexts);

    void postWiki(string keyword);

    
private:
    ofxHttpUtils httpUtils;
    int counter;
    string responseStr;
    string requestStr;
    string action_url;
    
    ofxTextWriter tr;
    ofTrueTypeFont font;
    
    float slider;
    bool playout;
    bool oscGetMessage;
    
    ofxOscReceiver  receiver;

    
};
