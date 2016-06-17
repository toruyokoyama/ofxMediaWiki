//
//  ofxMediaWiki.cpp
//  ofxwiki
//
//  Created by YOKOYAMA Toru on 2016/06/15.
//
//

#include "ofxMediaWiki.hpp"

ofxMediaWiki::ofxMediaWiki()
{
    
}

ofxMediaWiki::~ofxMediaWiki()
{
    
}

void ofxMediaWiki::setup(string postURL, int PORT)
{
    action_url = postURL;
    ofAddListener(httpUtils.newResponseEvent,this,&ofxMediaWiki::newResponse);
    httpUtils.start();
    slider = 0;
    playout = false;
    oscGetMessage = false;
    receiver.setup( PORT );
    oscGetMessage = false;

}

void ofxMediaWiki::setup(string postURL, int PORT, string fontName, int fontSize)
{
    action_url = postURL;
    ofAddListener(httpUtils.newResponseEvent,this,&ofxMediaWiki::newResponse);
    httpUtils.start();
    
    font.load(fontName, fontSize);
    slider = 0;
    playout = false;
    oscGetMessage = false;
    receiver.setup( PORT );
    oscGetMessage = false;

}

void ofxMediaWiki::oscUpdateMessage(string oscAddress){
    while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        receiver.getNextMessage( m );
        
        if ( m.getAddress() == oscAddress && oscGetMessage == false){
            string key = m.getArgAsString(0);
            int strPos = key.find(",");
            if (strPos != string::npos) {
                key.replace(strPos, (key.length()-strPos), "");
            }
            
            cout<<"KEY:"<<key<<endl;
            ofxHttpForm form;
            form.action = action_url;
            form.method = OFX_HTTP_POST;
            //form.addHeaderField("User-Agent", "Mozilla/4.0");
            form.addFormField("format", "xml");
            form.addFormField("action", "query");
            //form.addFormField("list", "nonredirects");
            form.addFormField("prop", "revisions");
            form.addFormField("titles", key);
            form.addFormField("rvprop", "content");
            
            httpUtils.addForm(form);
            oscGetMessage = true;
            
        }
        
    }

}

void ofxMediaWiki::textRender(string texts,int textSpeed, int stringColumn)
{
    tr.init();
    tr.resetTime();
    
    for (int i=stringColumn; i<texts.length(); i+=stringColumn) {
        texts.insert(i, "\n");
        
    }
    
    tr.setTimeToRender(textSpeed);
    tr.setTextToRender(texts);
    playout = true;
    slider = 0;
   
}

void ofxMediaWiki::TextUpdatePosition(float slideSpeed){
    ofRectangle rect = font.getStringBoundingBox(tr.whatToRender(), 0, 0);
    if (rect.getHeight() > ofGetHeight()-100) {
        slider -= slideSpeed;
        
        if (-slider >= rect.getHeight() + 50 && playout) {
            oscGetMessage = false;
            playout = false;
        }
    }

}


void ofxMediaWiki::drawTextAnimation(float setLineHeight, int margin_x, int margin_y){
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(0, slider);
    font.setLineHeight(setLineHeight);
    font.drawString(tr.whatToRender(), margin_x, margin_y);
    ofPopMatrix();
    
}

void ofxMediaWiki::newResponse(ofxHttpResponse & response){
    responseStr.clear();
    responseStr = (string)response.responseBody;
    
    
    eraseTwoCharAfterAll("==");
    eraseHeaderTexts("'''");
    eraseOneChar("'");
    eraseOneTwoChar("[");
    eraseOneTwoChar("]");
    eraseOneTwoChar("  ");
    eraseOneTwoChar("/n");
    eraseOneTwoChar("&quot");
    eraseTwoCharAfterAll("<!");
    eraseTwoCharAfterAll("<?");

   
    
    string firstTag = "&lt;ref";
    string secoundTag = "&lt;/ref";
    for(size_t c = responseStr.find(firstTag); c != string::npos; c = c = responseStr.find(firstTag)){
        
        int eraseCounterSecoundTag = responseStr.find(secoundTag);
        responseStr.erase(c,(eraseCounterSecoundTag - c) + 12);
        
    }

    
    
    std::ofstream ofs("/Users/to.yokoyama/Desktop/wikitext/coffee_revo.txt");
    ofs <<responseStr <<std::endl;
    
    if (responseStr.length() <= 300) {
        oscGetMessage = false;
        return;
    }
    
    
    
    
    tr.init();
    tr.resetTime();
    
    for (int i=31; i<responseStr.length(); i+=31) {
        responseStr.insert(i, "\n");
        
    }
    tr.setTimeToRender(responseStr.length()*0.01);
    tr.setTextToRender(responseStr);
    playout = true;
    slider = 0;

    
}


void ofxMediaWiki::eraseTwoCharAfterAll(string removeTexts){
    int eraseCounter = responseStr.find(removeTexts);
    if (eraseCounter != string::npos) {
        responseStr.erase(eraseCounter, responseStr.length() - eraseCounter);
    }
    
}



void ofxMediaWiki::eraseHeaderTexts(string removeTexts){
    int eraseCounterIndex = responseStr.find(removeTexts);
    if (eraseCounterIndex != string::npos) {
        responseStr.erase(0,eraseCounterIndex-1);
    }
}


void ofxMediaWiki::eraseOneTwoChar(string removeText){
    for(size_t c = responseStr.find(removeText); c != string::npos; c = c = responseStr.find(removeText)){
        responseStr.replace(c, removeText.length(), "");

    }
}

void ofxMediaWiki::eraseOneChar(string removeText){
    for(size_t c = responseStr.find_first_of(removeText); c != string::npos; c = c = responseStr.find_first_of(removeText)){
        responseStr.replace(c, 1, "");
        
    }
}

void ofxMediaWiki::postWiki(string keyword){
    string key = keyword;
    ofxHttpForm form;
    form.action = action_url;
    form.method = OFX_HTTP_POST;
    //form.addHeaderField("User-Agent", "Mozilla/4.0");
    form.addFormField("format", "xml");
    form.addFormField("action", "query");
    //form.addFormField("list", "nonredirects");
    form.addFormField("prop", "revisions");
    form.addFormField("titles", key);
    form.addFormField("rvprop", "content");
    
    httpUtils.addForm(form);
}



