#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // songs
    unexCoder(3);
    //------------SETUPS AND START AUDIO-------------
    engine.listDevices();
    engine.setDeviceID(2); // SET THIS AT RIGHT INDEX!!!!
    engine.setup( 44100, 512, 3);
    
    engine.audio_out(0) >> scope >> engine.blackhole();
    engine.audio_out(1) >> scope >> engine.blackhole();
    
    engine.sequencer.stop();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255, 125, 95);
    scope.draw(0, 0, ofGetWidth(), ofGetHeight());
    string info = "master playhead (bars): ";
    info += to_string( engine.sequencer.meter_playhead() );
    ofDrawBitmapString(info, 20, ofGetHeight()-20 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // we can launch our sequences with the launch method, with optional quantization
    switch (key){
        case '1':
            engine.sequencer.sections[0].launch(0,quantize,quantime);
            break;
        case '2':
            engine.sequencer.sections[1].launch(0,quantize,quantime);
            break;
        case '3':
            engine.sequencer.sections[2].launch(0,quantize,quantime);
            break;
        case '4':
            engine.sequencer.sections[3].launch(0,quantize,quantime);
            break;
        case '5':
            engine.sequencer.sections[4].launch(0,quantize,quantime);
            break;
        case '6':
            engine.sequencer.sections[5].launch(0,quantize,quantime);
            break;
        case '7':
            engine.sequencer.sections[6].launch(1,quantize,quantime);
            break;
        case '8':
            engine.sequencer.sections[7].launch(1,quantize,quantime);
            break;
        case '9':

            break;
        case '0':

            break;
        case 'q':

            break;
        case 'w':

            break;
        case 'e':

            break;
        case 'r':

            break;
        case 't':
            
            break;
            
        case 'a':

            break;
        case ' ': // pause / play
            if(engine.sequencer.isPlaying()){
                engine.sequencer.pause();
            }else{
                engine.sequencer.play();
            }
            break;
        case 's': // stop
            engine.sequencer.stop();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::unexCoder(int s){
    switch (s) {
        {
            // ITERATION 0
        case 1:
            /////////////////
            // HAIKU      //
            ////////////////

            angel.load("/Users/Luigi/Documents/work/wav/samples/angel1.wav");
            drone.setup(0,0);
            drone.addSample(angel);
            
            // sequences settings
            seq_mode = 0;
            quantize = true;
            quantime = 1.0/16.0; // 1/8th
            
            // masterplan
            engine.sequencer.init( 5, 5, 128.0f); // sections, sequences, tempo
            engine.sequencer.sections[0].resizeCells(1);
            engine.sequencer.sections[0].sequence(0).label = "masterplan";
            engine.sequencer.sections[0].sequence(0).bars =  1.0 / 8.0;
            
            engine.sequencer.sections[0].sequence(0).code = [&] () noexcept { // masterplan sequence
                
                pdsp::Sequence & seq = engine.sequencer.sections[0].sequence(0); // defining variable into the lambda is fine
                // metric
                int beat = (seq.counter()) % 4;
                int bar = seq.counter() / 4;
                cout << std::to_string(bar) + ":" + std::to_string(beat) << endl;
                
                int index = seq.counter()%16; // we repeat the same states four time, so each pattern is 2 bars
                
                // main flow
                if ((bar == 0)&&(index % 4 == 0)) {
                    engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                }
                
                if ((bar == 3)&&(beat  == 0)) {
                    engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                }
                
                if ((bar == 12)&&(beat  == 0)){
                    engine.sequencer.sections[4].launch(0,true,seq.length());
                    drone.ch(0) * dB(0.0f)  >> reverb >> engine.audio_out(0);
                    drone.ch(1) * dB(0.0f)  >> reverb >> engine.audio_out(1);
                }
                if ((bar == 28)&&(beat  == 0)) {
                    drone.positionControl.set(0.19f);
                }
                if ((bar == 48)&&(beat  == 0)) {
                    engine.sequencer.sections[2].launchCell( 0, true, seq.length());
                    drone.positionControl.set(0.2f);
                    engine.sequencer.sections[4].launch(0,true,seq.length());
                }
                if ((bar == 64)&&(beat  == 0)) {
                    drone.positionControl.set(0.21f);
                }
                if ((bar == 92)&&(beat  == 0)) {
                    drone.positionControl.set(0.2f);
                    engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                }
                if ((bar == 108)&&(index % 4 == 0)) {
                    drone.positionControl.set(0.19f);
                    engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[2].launch(0,true,seq.length());
                }
                if ((bar == 136)&&(beat  == 0)) {
                    drone.positionControl.set(0.2f);
                    engine.sequencer.sections[4].launch(1,true,seq.length());
                }
                if ((bar == 150)&&(beat  == 3)) {
                    engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[4].launchCell( 2, true, seq.length());
                }
                if ((bar == 156)&&(beat  == 0)) {
                    engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                    drone.ch(0) * dB(-90.0f)  >> engine.audio_out(0);
                    drone.ch(1) * dB(-90.0f)  >> engine.audio_out(1);
                }
                if ((bar == 164)&&(beat  == 0)) {
                    drone.ch(0) * dB(-90.0f)  >> reverb;
                    drone.ch(1) * dB(-90.0f)  >> reverb;
                engine.sequencer.stop();
                }

            };
            //
            engine.sequencer.sections[1].out_trig(0)  >> kick.in("trig");
            engine.sequencer.sections[2].out_trig(0)  >> snare.in("trig");
            engine.sequencer.sections[3].out_trig(0)  >> bass2.in("trig");
            engine.sequencer.sections[3].out_value(1) >> bass2.in("pitch");
            
            fmsynth.setup(3);
            
            for ( size_t i = 0; i<3; ++i ){
                engine.sequencer.sections[4].out_trig( i*2 ) >> fmsynth.voices[i].in("trig");
                engine.sequencer.sections[4].out_value( i*2 + 1 ) >> fmsynth.voices[i].in("pitch");
            }
            //------------------------------------
            
            float o = -1.0f; // "set" negative outputs are ignored, 'o' is graphically useful
            
            // kick sequences
            kick_seqs.resize(1);
            kick_seqs[0].steplen = 1.0/16.0;
            kick_seqs[0].bars = 2.0; // this can also be omitted, 1.0 is the default value
            kick_seqs[0].set( {
                1.0f, o, o, o, o, o, o, o, 1.0f, o, o, o, o, o, o, o,
                1.0f, o, o, o, o, o, o, o, 1.0f, o, o, o, o, o, 1.0f, 1.0f} );
            
            // percu sequences
            snare_seqs.resize(1);
            snare_seqs[0].steplen = 1.0/8.0;
            snare_seqs[0].set(  { 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f });

            // bass sequences
            bass_seqs.resize(1);
            bass_seqs[0].steplen = 1.0/16.0;
            bass_seqs[0].set( { { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,
                                  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f}, //trigs
                { o, o,     o,  o,     o, o,    35.0f, o,
                  35.0f, o, 35.0f, o,  38.0f, o,o, o } });//pitch

            // organo Bm---C#m---Em---Bm---
            // """""" Bm---Amaj7---Dmaj7---Gmaj7---
            // """""" D---Gmaj7---D---Gmaj7---
            // choral sequences
            fmpad_seqs.resize(3);
            fmpad_seqs[0].bars = 22.0;
            fmpad_seqs[0].steplen = 2.0;
            fmpad_seqs[0].set( { { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  1.0f }, //trigs
                { 71.0f,73.0f,71.0f,71.0f,71.0f,69.0f,73.0f,67.0f,69.0f,67.0f,69.0f},
                                 { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  1.0f }, //trigs
                { 74.0f,76.0f,76.0f,74.0f,74.0f,73.0f,74.0f,71.0f,74.0f,71.0f,74.0f},
                                 { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  1.0f }, //trigs
                { 78.0f,80.0f,79.0f,78.0f,78.0f,80.0f,78.0f,78.0f,78.0f,78.0f,78.0f}});

            fmpad_seqs[1].bars = 8.0;
            fmpad_seqs[1].steplen = 2.0;
            fmpad_seqs[1].set( { { 1.0f, 1.0f,  1.0f,  1.0f }, //trigs
                { 67.0f,69.0f,67.0f,69.0f},
                {  1.0f, 1.0f,  1.0f,  1.0f }, //trigs
                { 71.0f,74.0f,71.0f,74.0f},
                {  1.0f, 1.0f,  1.0f,  1.0f }, //trigs
                { 78.0f,78.0f,78.0f,78.0f}});
            
            fmpad_seqs[2].bars = 2.0;
            fmpad_seqs[2].steplen = 2.0;
            fmpad_seqs[2].set( { { 1.0f, 1.0f }, //trigs
                { 69.0f},
                { 1.0f }, //trigs
                { 74.0f},
                {  1.0f }, //trigs
                { 78.0f}});
            // granular lady
            //
            // assigning the sequences to the sequencer sections
            for(int i = 0; i<3; ++i){
                // arguments: cell index, pointer to pdsp:Sequence, behavior (pdsp::Behavior::Loop if not given)
                engine.sequencer.sections[1].setCell(i, kick_seqs[i]);
                engine.sequencer.sections[2].setCell(i, snare_seqs[i]);
                engine.sequencer.sections[3].setCell(i, bass_seqs[i]);
                engine.sequencer.sections[4].setCell(i, fmpad_seqs[i]);
            }
            
            // synth args
            30.0f >> kick.in("pitch");
            30.0f >> kick.in("pitch_fall");
            120.0f >> kick.in("release");
            fmsynth.fm_ctrl.set(0.15f);
            fmsynth.self_ctrl.set(0.0f);
            fmsynth.self_mod.set(0.0f);
            fmsynth.ratio_ctrl.set(0.5f);
            fmsynth.env_release_ctrl.set(555.5f);
            drone.densityControl.set(0.1f);
            drone.smoothing(0.0f);
            drone.positionControl.set(0.2f);
            30.0f >> snare.in("noiseRelease");
            599.5f >> snare.in("release");
            // FX
            0.5f >> reverb.in_time();
            
            // patching (with panning)
            kick * (dB(-7.5f) * pdsp::panL(0.0f))  >> engine.audio_out(0);
            kick * (dB(-7.5f) * pdsp::panR(0.0f))  >> engine.audio_out(1);
            
            snare * (dB(1.5f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            snare * (dB(1.5f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

            bass2 * (dB(-9.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            bass2 * (dB(-9.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

            fmsynth.ch(0) * dB(-31.0f) >> engine.audio_out(0);
            fmsynth.ch(1) * dB(-31.0f) >> engine.audio_out(1);

            //drone.ch(0) * dB(-6.0f)  >> reverb >> engine.audio_out(0);
            //drone.ch(1) * dB(-6.0f)  >> reverb >> engine.audio_out(1);
            drone.ch(0) * dB(-12.0f)  >> engine.audio_out(0);
            drone.ch(1) * dB(-12.0f)  >> engine.audio_out(1);
            
            break;
        }
        {
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            
        case 2:
            /////////////////////
            // (LUNNAR) LANDER  //
            /////////////////////
            
            // sequences settings
            seq_mode = 0;
            quantize = true;
            quantime = 1.0/8.0; // 1/4th
            
            // masterplan
            engine.sequencer.init( 7, 5, 60.0f); // sections, sequences, tempo
            engine.sequencer.sections[0].resizeCells(1);
            engine.sequencer.sections[0].sequence(0).label = "masterplan";
            engine.sequencer.sections[0].sequence(0).bars =  1.0 / 8.0;
            
            engine.sequencer.sections[0].sequence(0).code = [&] () noexcept { // masterplan sequence
                
                pdsp::Sequence & seq = engine.sequencer.sections[0].sequence(0); // defining variable into the lambda is fine
                // metric
                int beat = (seq.counter()) % 4;
                int bar = seq.counter() / 4;
                cout << std::to_string(bar) + ":" + std::to_string(beat) << endl;
                
                // main flow >> 85cc
                if ((bar == 0)&&(beat == 0)) {
                    engine.sequencer.setTempo(60.0f);
                    engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                }
                if ((bar == 28)&&(beat == 0)) {
                    engine.sequencer.setTempo(86.0f);
                    engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[2].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[4].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[5].launchCell( 0, true, seq.length());
                }
                if (bar == 56) {
                    engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                }
                if (bar == 57) {
                    engine.sequencer.sections[6].launchCell( 0, true, seq.length());
                }
                if ((bar == 78)&&(beat == 0)) {
                    engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[5].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[6].launchCell( -1, true, seq.length());
                }
                if ((bar == 81)&&(beat == 3)) {
                    engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                }
                if ((bar == 82)&&(beat == 0)) {
                    engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[2].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[5].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[6].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[4].launchCell( 0, true, seq.length());
                }
                if ((bar >= 90)&&(bar <= 138)) {
                    if ((beat % 2 == 0)||(beat % 2 == 3)) {
                        engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                    }
                }
                if (bar == 138) {
                    engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[5].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[6].launchCell( -1, true, seq.length());
                    engine.sequencer.stop();
                    // end //////////////////////////////////////////////////////////
                }
            };
            
            engine.sequencer.sections[1].out_trig(0)  >> kick.in("trig");
            engine.sequencer.sections[2].out_trig(0)  >> perc.in("trig");
            engine.sequencer.sections[2].out_value(1) >> perc.in("pitch");
            engine.sequencer.sections[4].out_trig(0)  >> bass.in("trig");
            engine.sequencer.sections[4].out_value(1) >> bass.in("pitch");
            engine.sequencer.sections[5].out_trig(0)  >> hat.in("trig");
            engine.sequencer.sections[5].out_value(1)  >> hat.in("release");
            engine.sequencer.sections[6].out_trig(0)  >> perc2.in("trig");
            engine.sequencer.sections[6].out_value(1) >> perc2.in("pitch");
            fmsynth.setup(4);
            
            for ( size_t i = 0; i<4; ++i ){
                engine.sequencer.sections[3].out_trig( i*2 ) >> fmsynth.voices[i].in("trig");
                engine.sequencer.sections[3].out_value( i*2 + 1 ) >> fmsynth.voices[i].in("pitch");
            }
            
            // synth args
            48.0f >> kick.in("pitch");
            36.0f >> kick.in("pitch_fall");
            //------------------------------------
            
            float o = -1.0f; // "set" negative outputs are ignored, 'o' is graphically useful
            
            // kick sequences
            kick_seqs.resize(1);
            kick_seqs[0].steplen = 1.0/16.0;
            kick_seqs[0].bars = 2.0; // this can also be omitted, 1.0 is the default value
            kick_seqs[0].set( {1.0f, o, o, 1.0f,1.0f, o, o, 1.0f,
                               1.0f, 1.0f, o, 1.0f,1.0f, o, o, 1.0f,
                               1.0f, o, o, 1.0f,1.0f, o, o, 1.0f,
                               1.0f, 1.0f, o, 1.0f,1.0f, o, o, 1.0f
            } );

            // bass sequences
            bass_seqs.resize(2);
            bass_seqs[0].steplen = 1.0/16.0;
            bass_seqs[0].bars = 2.0; // this can also be omitted, 1.0 is the default value
            bass_seqs[0].set( {{1.0f, 0.0f, o, 1.0f,1.0f, 0.0f, o, 1.0f,
                               1.0f, 1.0f, 0.0f, 1.0f,1.0f, 0.0f, o, 1.0f,
                               1.0f, 0.0f, o, 1.0f,1.0f, 0.0f, o, 1.0f,
                               1.0f, 1.0f, 0.0f, 1.0f,1.0f, 0.0f, o, 1.0f}, // trigs
                             
                              {29.0f, o, o,29.0f,34.0f, o, o, 29.0f,
                               29.0f, 29.0f, o, 29.0f,34.0f, o, o, 29.0f,
                               29.0f, o, o, 29.0f,34.0f, o, o, 29.0f,
                               29.0f, 29.0f, o, 29.0f,34.0f, o, o, 29.0f} });// pitchs)
    
            // hihat sequences
            hihat_seqs.resize(1);
            hihat_seqs[0].steplen = 1.0/16.0;
            hihat_seqs[0].set( { {1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f,
                                  1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f }, //trigs
                               { 70.0f, 70.0f, 250.0f, 70.0f, 70.0f, 70.0f, 250.0f,70.0f,
                                70.0f, 70.0f, 250.0f, 70.0f, 70.0f, 70.0f, 250.0f, 70.0f} });//release
            
            // percu sequences
            percu_seqs.resize(1);
            percu_seqs[0].steplen = 1.0f/32.0f;
            percu_seqs[0].bars = 1.5f;
            percu_seqs[0].set( { {o, o, o, o, 1.0f, o, o, o, o, o, 1.0f, o, o, o, o, o,
                                  o, o, o, o, 1.0f, o, o, o, o, o, 1.0f, o, o, o, 1.0f, o,
                                  o, o, o, o, 1.0f, o, o, o, o, o, 1.0f, o, o, o, o, o }, //trigs
                { 84.0f } });//pitch
            
            // percu sequences
            snare_seqs.resize(1);
            snare_seqs[0].steplen = 1.0f/32.0f;
            snare_seqs[0].bars = 1.5f;
            snare_seqs[0].set( { {
                o, o, o, o, 1.0f, o, o, o, o, o, 1.0f, o, o, o, o, o,
                o, o, o, o, 1.0f, o, o, o, o, o, 1.0f, o, o, o, 1.0f, o,
                o, o, o, o, 1.0f, o, o, o, 1.0f, o, 1.0f, o, o, o, o, o
            }, //trigs
                { 90.0f } });//pitch
            
            // choral sequences
            fmpad_seqs.resize(1);
            fmpad_seqs[0].bars = 7.0f;
            fmpad_seqs[0].steplen = 1.0f/4.0f;

            // color nuevo
            static float color[] = { 41.0f, 44.0f, 45.0f, 44.0f, 40.0f, 37.0f,45.0f,46.0f,38.0f,39.0f,36.0f  };
            // talea
            static float talea[] = { 1.0f, o, o, 1.0f, o, o, o,
                                     1.0f, o, o, 1.0f, o, o, o,
                                     1.0f, o, o, o, 1.0f, o, o,
                                     1.0f,o, o, o, o, o, o
            };
            static float duras[] = { 2.85f, o, o, 3.5f, o, o, o,
                                     2.85f, o, o, 3.5f, o, o, o,
                                     3.85f, o, o, o, 2.85f, o, o,
                                     5.0,o , o, o, o, o, o
            };
            
            // lambda love
            fmpad_seqs[0].code = [&] () noexcept { // better to tag noexcept for code used by the DSP engine
                pdsp::Sequence & seq = fmpad_seqs[0]; // reference
                
                seq.steplen = 1.0/4.0;
                seq.begin();
                for (int i=0; i<26; ++i){
                    if (talea[i] != -1) {
                        // talea
                        seq.message( double(i), talea[i],  0 );
                        seq.message( double(i)+duras[i], 0.0f,  0 );
                        seq.message( double(i), color[indexC % 11]+12, 1 );
                        
                        //
                        int c = 0;int s = 0;
                        // solo tríadas mayores y menores
                        int chance = pdsp::dice(3);
                        int chance2;
                        if (chance < 1) {
                            c = 3;
                        } else if ((chance >= 1) && (chance < 2)) {
                            c = 4;
                        } else if ((chance >= 2) && (chance < 3)) {
                            c = 5;
                        }
                        
                        if ((c == 3)||(c == 4)) {
                            chance2 = pdsp::dice(2);
                            if (chance2 < 1) {
                                s = 7;
                            } else if ((chance2 >= 1) && (chance2 < 2)) {
                                if (c == 3) {
                                    s = 8;
                                } else {
                                    s = 9;
                                }
                            }
                        } else if (c == 5) {
                            chance2 = pdsp::dice(2);
                            if (chance2 < 1) {
                                s = 8;
                            } else if (chance2 >= 1){
                                s = 9;
                            }
                        }

                        seq.message( double(i), talea[i],  2 );
                        seq.message( double(i)+duras[i], 0.0f,  2 );
                        seq.message( double(i), color[indexC % 11]+12+c, 3 );

                        seq.message( double(i), talea[i],  4 );
                        seq.message( double(i)+duras[i], 0.0f,  4 );
                        seq.message( double(i), color[indexC % 11]+12+s, 5 );

                        indexC++;
                    }
                }
                //cout << indexC << endl;
                seq.end();
            };
            
            // assigning the sequences to the sequencer sections
            for(int i = 0; i<1; ++i){
                // arguments: cell index, pointer to pdsp:Sequence, behavior (pdsp::Behavior::Loop if not given)
                engine.sequencer.sections[1].setCell(i, kick_seqs[i]);
                engine.sequencer.sections[2].setCell(i, percu_seqs[i]);
                engine.sequencer.sections[3].setCell(i, fmpad_seqs[i]);
                engine.sequencer.sections[4].setCell(i, bass_seqs[i]);
                engine.sequencer.sections[5].setCell(i, hihat_seqs[i]);
                engine.sequencer.sections[6].setCell(i, snare_seqs[i]);
            }

            // synth args
            fmsynth.fm_ctrl.set(0.5f);
            fmsynth.self_ctrl.set(0.025f);
            fmsynth.self_mod.set(0.1f);
            fmsynth.ratio_ctrl.set(1.0f);
            0.4f >> bass.in("index");
            5.0f >> bass.in("attack");
            870.0f >> bass.in("release");
            36.0f >> kick.in("pitch");
            36.0f >> kick.in("pitch_fall");
            999.0f >> bass.in("release");
            110.0f >> perc.in("release");
            499.4f >> perc2.in("release");
            // fx args
            1.25f >> reverb.in_time();
            
            // patching (with panning)
            kick * (dB(-12.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            kick * (dB(-12.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);
            
            perc * (dB(3.0f) * pdsp::panL(0.25f)) >> engine.audio_out(0);
            perc * (dB(3.0f) * pdsp::panR(0.25f)) >> engine.audio_out(1);
            perc2 * (dB(3.0f) * pdsp::panL(0.25f)) >> engine.audio_out(0);
            perc2 * (dB(3.0f) * pdsp::panR(0.25f)) >> engine.audio_out(1);

            fmsynth.ch(0) * dB(-21.0f) >> reverb;
            fmsynth.ch(1) * dB(-21.0f) >> reverb;
            
            bass * (dB(-18.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            bass * (dB(-18.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

            hat * (dB(-5.0f) * pdsp::panL(-0.25f)) >> engine.audio_out(0);
            hat * (dB(-5.0f) * pdsp::panR(-0.25f)) >> engine.audio_out(1);
            hat * dB(-21.0f) >> reverb;
            
            reverb.ch(0) >> engine.audio_out(0);
            reverb.ch(1) >> engine.audio_out(1);
            break;
        }
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
        {
        case 3:
            //////////
            // REM
            //////////
            // sequences settings
            seq_mode = 0;
            quantize = true;
            quantime = 1.0/8.0; // 1/4th
            //
            // masterplan
            engine.sequencer.init( 8, 5, 61.0f); // sections, sequences, tempo
            engine.sequencer.sections[0].resizeCells(1);
            engine.sequencer.sections[0].sequence(0).label = "masterplan";
            engine.sequencer.sections[0].sequence(0).bars =  1.0 / 8.0;
            
            engine.sequencer.sections[0].sequence(0).code = [&] () noexcept { // masterplan sequence
                
                pdsp::Sequence & seq = engine.sequencer.sections[0].sequence(0); // defining variable into the lambda is fine
                // metric
                int beat = (seq.counter()) % 4;
                int bar = seq.counter() / 4;
                cout << std::to_string(bar) + ":" + std::to_string(beat) << endl;

                int index = seq.counter()%16; // we repeat the same states four time, so each pattern is 2 bars

                // main flow >>  +-60 cc
                if ((bar == 0)&&(index % 4 == 0)) {
                    engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[2].launchCell( 0, true, seq.length());
                }
                if ((bar == 2)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[4].launchCell( 0, true, seq.length());
                }
                if ((bar == 10)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[5].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[6].launchCell( 1, true, seq.length());
                }
                if ((bar == 18)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 0, true, seq.length());
                }
                if ((bar == 30)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 1, true, seq.length());
                }
                if ((bar == 46)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 2, true, seq.length());
                }
                if ((bar == 56)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 3, true, seq.length());
                }
                if ((bar == 64)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 1, true, seq.length());
                }
                if ((bar == 82)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 4, true, seq.length());
                }
 
                if (bar == 93) {
                    if (beat  == 3) {
                        engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                        engine.sequencer.sections[5].launchCell( -1, true, seq.length());
                        engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                        engine.sequencer.sections[6].launchCell( -1, true, seq.length());
                    }
                }
                
                if ((bar == 101)&&(beat  == 3)) {
                    engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                }
                if ((bar == 102)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 0, true, seq.length());
                }
                if ((bar == 110)&&(beat  == 0)) {
                    engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                }
                if ((bar == 114)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[5].launchCell( 0, true, seq.length());
                }
                if ((bar == 118)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                }
                if ((bar == 120)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                }
                if ((bar == 126)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[6].launchCell( 1, true, seq.length());
                }
                if ((bar == 134)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[2].launchCell( 0, true, seq.length());
                    engine.sequencer.sections[4].launchCell( 0, true, seq.length());
                }
                if ((bar == 140)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[7].launchCell( 2, true, seq.length());
                }
                if ((bar == 158)&&(beat  == 0)&&(index % 2  == 0)) {
                    engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[5].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[6].launchCell( -1, true, seq.length());
                    engine.sequencer.sections[7].launchCell( -1, true, seq.length());
                    engine.sequencer.stop();
                    // end //////////////////////////////////////////////////////////
                }
                // melo
                // mib-------re---------sib---do---------sol----la-----------------------------
                // mib-------re---------sib---do---------sol---- sol·---------la --------------------
            };
            //

            engine.sequencer.sections[1].out_trig(0)  >> kick.in("trig");
            engine.sequencer.sections[2].out_trig(0)  >> perc.in("trig");
            engine.sequencer.sections[2].out_value(1) >> perc.in("pitch");
            engine.sequencer.sections[3].out_trig(0)  >> snare.in("trig");
            engine.sequencer.sections[5].out_trig(0)  >> bass.in("trig");
            engine.sequencer.sections[5].out_value(1) >> bass.in("pitch");
            engine.sequencer.sections[6].out_trig(0)  >> hat.in("trig");
            engine.sequencer.sections[6].out_value(1)  >> hat.in("release");
            //------------------------------------
            
            float o = -1.0f; // "set" negative outputs are ignored, 'o' is graphically useful
            
            // kick sequences
            kick_seqs.resize(1);
            kick_seqs[0].steplen = 1.0/32.0;
            kick_seqs[0].bars = 15.0f/16.0f; // this can also be omitted, 1.0 is the default value
            kick_seqs[0].set( {
                1.0f, o, o, o,
                o, o,1.0f, o,
                o, o, o, o,
                1.0f, o, o, o,
                o, o,1.0f, o,
                o, o, o, o ,
                o, o, o, o,
                1.0f, 1.0f } );
            
            // percu sequences
            percu_seqs.resize(1);
            percu_seqs[0].steplen = 1.0/32.0;
            percu_seqs[0].bars = 15.0f/16.0f;
            percu_seqs[0].set( {
                {o, o, o, o,
                    1.0f, o,o, o,
                    o, o, 1.0f, o,
                    o, o, o, o,
                    1.0f, o, o, o,
                    o, o, 1.0f, o,
                    o, o, o, o,
                    o, o}, //trigs
                
                {o,o,o,o,
                    84.0f,o,o,o,
                    o,o,o,84.0f,
                    o,o,o,o,
                    84.0f,o,o,o,
                    o,o,84.0f,o,
                    o,o,o,o,
                    o,o} });//pitch
            
            // snare seqs
            snare_seqs.resize(1);
            snare_seqs[0].steplen = 1.0/32.0;
            snare_seqs[0].bars = 3.0f; // this can also be omitted, 1.0 is the default value
            snare_seqs[0].set( {
                o, o,o, o, 1.0f, o,o,o,
                o, o,o, o,1.0f, o,o,o,
                o, o,o, o, 1.0f, o,o,o,
                o, o,o, o, 1.0f, o,o,o,
                o, o,o, o,1.0f, o,o,o,
                o, o,o, o, 1.0f, o ,o,o,
                o, o,o, o, 1.0f, o,o,o,
                o,o, o,o,1.0f,1.0f, 1.0f,o,
                o, o,o, o, 1.0f, o,o,o,
                o, o,o, o,1.0f, o,o,o,
                o, o,o, o, 1.0f, o,o,o,
                o, o,o, o, 1.0f, o,o,o
            } );

            // hat seqs
            hihat_seqs.resize(2);
            hihat_seqs[0].steplen = 1.0/32.0;
            hihat_seqs[0].bars = 1.0f; // this can also be omitted, 1.0 is the default value
            hihat_seqs[0].set( {
                1.0f, 1.0f,1.0f, 1.0f, 1.0f, 1.0f,1.0f,1.0f,
                1.0f, 1.0f,1.0f, 1.0f,1.0f, 1.0f,1.0f,1.0f,
                1.0f, 1.0f,1.0f, 1.0f, 1.0f, 1.0f,1.0f,1.0f,
                1.0f, 1.0f,1.0f, 1.0f,1.0f, 1.0f,1.0f,1.0f
            } );
            //
            // lambda love
            hihat_seqs[1].code = [&] () noexcept { // better to tag noexcept for code used by the DSP engine
                pdsp::Sequence & seq = hihat_seqs[1]; // reference
                
                seq.steplen = 1.0/32.0;
                seq.begin();
                for (int i=0; i<32; ++i){
                    float trig = (i%2==0) ? 1.0f : 0.75f;
                    //float release = pdsp::urand()*250.0f;
                    float release = (pdsp::dice(7)<=5) ? 70.0f : 250.0f;
                    seq.message( double(i),       trig,  0 );
                    seq.message( double(i)+0.6f,  0.0f,  0 ); // trigger off, half step gate
                    seq.message( double(i),       release, 1 );
                }
                seq.end();
            };
            
            //
            // bass sequences
            bass_seqs.resize(1);
            bass_seqs[0].steplen = 1.0/32.0;
            bass_seqs[0].bars = 1.0f;
            bass_seqs[0].set( {
                {o, o, o, o,
                    1.0f, 0.0f,o, o,
                    o, o, 1.0f, 0.0f,
                    o, o, o, o,
                    1.0f, 0.0f, o, o,
                    o, o, 1.0f, 0.0f,
                    o, o, o, o,
                    o, o,o, o}, //trigs
                
                {o,o,o,o,
                    36.0f,o,o,o,
                    o,o,o,36.0f,
                    o,o,o,o,
                    36.0f,o,o,o,
                    o,o,36.0f,o,
                    o,o,o,o,
                    o,o,o, o} });//pitch

            // poly sequences
            poly_seq.resize(1);
            poly_seq[0].steplen = 1.0/12.0;
            poly_seq[0].bars = 16.0f/16.0f;
            poly_seq[0].set( { { 1.0f,  o,  0.75f,  0.0f,  1.0f,  0.0f, 0.75f, 0.0f }, //trigs
                { 60.0f, o,     58.0f,  o,     65.0f, o,    58.0f, o,65.0f, o,    58.0f, o},
                { 1.0f,  o,  0.75f,  0.0f,  1.0f,  0.0f, 0.75f, 0.0f }, //trigs
                { 67.0f, o,     58.0f,  o,     60.0f, o,    56.0f, o,65.0f, o,    67.0f, o},
                { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f }, //trigs
                { 48.0f}
                
            });

            // melo
            // mib-------re---------sib---do---------sol----la-----------------------------
            // mib-------re---------sib---do---------sol---- sol·---------la --------------------
            // melody sequences
            fmpad_seqs.resize(5);
            fmpad_seqs[0].steplen = 1.0/8.0;
            fmpad_seqs[0].bars = 5.0f;
            fmpad_seqs[0].set( {
            { 1.0f,o,o,o,o,o,o,0.0, 1.0f,o,o,o,o,o,0.0,1.0,0.0,1.0f,o,o,o,o,0.0, 1.0f,o,o,o,o,0.0,1.0f,o,o,o,o,o,o,o,o,o,0.0}, //trigs
            { 75.0f,o,o,o,o,o,o,o,  74.0f,o,o,o,o,o,o,70.0f,o,72.0f,o,o,o,o,o, 67.0f,o,o,o,o,o,69.0f,o,o,o,o,o,o,o,o,o,o},
                //pitchs
            { 1.0f,o,o,o,o,o,o,0.0, 1.0f,o,o,o,o,o,0.0,1.0,0.0,1.0f,o,o,o,o,0.0, 1.0f,o,o,o,o,0.0,1.0f,o,o,o,o,o,o,o,o,o,0.0}, //trigs
            { 87.0f,o,o,o,o,o,o,o,  86.0f,o,o,o,o,o,o,82.0f,o,84.0f,o,o,o,o,o, 79.0f,o,o,o,o,o,81.0f,o,o,o,o,o,o,o,o,o,o}
                //pitchs
            });

            fmpad_seqs[1].steplen = 1.0/8.0;
            fmpad_seqs[1].bars = 6.0f;
            fmpad_seqs[1].set( {
            {1.0f,o,o,o,o,o,o,0.0, 1.0f,o,o,o,o,o,0.0,1.0,  o,o,0.0,1.0f,o,o,o,0.0f,  1.0f,o,o,o,0.0,1.0f,o,o,o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0f}, //trigs
            {75.0f,o,o,o,o,o,o,o,  74.0f,o,o,o,o,o,o,70.0f, o,o,o,72.0f,o,o,o,o,
                67.0f,o,o,o,o,68.0f,o,o,o,o,o,o,o,69.0f,o,o,  o,o,o,o,o,o,o,o},
                //pitchs
            {1.0f,o,o,o,o,o,o,0.0, 1.0f,o,o,o,o,o,0.0,1.0,  o,o,0.0,1.0f,o,o,o,0.0f,  1.0f,o,o,o,0.0,1.0f,o,o,o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0f}, //trigs
            {87.0f,o,o,o,o,o,o,o,  86.0f,o,o,o,o,o,o,82.0f, o,o,o,84.0f,o,o,o,o,
                79.0f,o,o,o,o,80.0f,o,o,o,o,o,o,o,81.0f,o,o, o,o,o,o,o,o,o,o}
                //pitchs
            });
            
            fmpad_seqs[2].steplen = 1.0/8.0;
            fmpad_seqs[2].bars = 4.0f;
            fmpad_seqs[2].set( {
            { 1.0f,o,o,o,o,o,0.0,1.0,   0.0,1.0f,o,o,o,o,0.0,1.0f,  o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0}, //trigs
            { 70.0f,o,o,o,o,o,o, 68.0f, o, 71.0f,o,o,o,o,o,  67.0f, o,o,o,o,o, 70.0f,o,o,  o,o,o,o,o,o,o,o}, //pitchs
            { 1.0f,o,o,o,o,o,0.0,1.0,   0.0,1.0f,o,o,o,o,0.0,1.0f,  o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0}, //trigs
            { 82.0f,o,o,o,o,o,o, 80.0f, o, 83.0f,o,o,o,o,o,  79.0f, o,o,o,o,o, 82.0f,o,o,  o,o,o,o,o,o,o,o} //pitchs
            });
            
            fmpad_seqs[3].steplen = 1.0/8.0;
            fmpad_seqs[3].bars = 4.0f;
            fmpad_seqs[3].set( {
                { 1.0f,o,o,o,o,o,0.0,1.0,   0.0,1.0f,o,o,o,o,0.0,1.0f,  o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0}, //trigs
                { 78.0f,o,o,o,o,o,o, 74.0f, o, 77.0f,o,o,o,o,o,  71.0f, o,o,o,o,o, 74.0f,o,o,  o,o,o,o,o,o,o,o}, //pitchs
                { 1.0f,o,o,o,o,o,0.0,1.0,   0.0,1.0f,o,o,o,o,0.0,1.0f,  o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0}, //trigs
                { 90.0f,o,o,o,o,o,o, 86.0f, o, 89.0f,o,o,o,o,o,  83.0f, o,o,o,o,o, 86.0f,o,o,  o,o,o,o,o,o,o,o} //pitchs
            });

            fmpad_seqs[4].steplen = 1.0/8.0;
            fmpad_seqs[4].bars = 4.0f;
            fmpad_seqs[4].set( {
                { 1.0f,o,o,o,o,o,0.0,1.0,   0.0,1.0f,o,o,o,o,0.0,1.0f,  o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0}, //trigs
                { 78.0f,o,o,o,o,o,o, 74.0f, o, 77.0f,o,o,o,o,o,  75.0f, o,o,o,o,o, 74.0f,o,o,  o,o,o,o,o,o,o,o}, //pitchs
                { 1.0f,o,o,o,o,o,0.0,1.0,   0.0,1.0f,o,o,o,o,0.0,1.0f,  o,o,o,o,0.0,1.0f,o,o, o,o,o,o,o,o,o,0.0}, //trigs
                { 90.0f,o,o,o,o,o,o, 86.0f, o, 89.0f,o,o,o,o,o,  87.0f, o,o,o,o,o, 86.0f,o,o,  o,o,o,o,o,o,o,o} //pitchs
            });
            
            synth.setup( 4  );
            
            for ( size_t i = 0; i<4; ++i ){
                engine.sequencer.sections[4].out_trig( i*2 ) >> synth.voices[i].in("trig");
                engine.sequencer.sections[4].out_value( i*2 + 1 ) >> synth.voices[i].in("pitch");
            }
            
            fmsynth.setup( 2  );
            
            for ( size_t i = 0; i<2; ++i ){
                engine.sequencer.sections[7].out_trig( i*2 ) >> fmsynth.voices[i].in("trig");
                engine.sequencer.sections[7].out_value( i*2 + 1 ) >> fmsynth.voices[i].in("pitch");
            }
            
            // assigning the sequences to the sequencer sections
            for(int i = 0; i<5; ++i){
                // arguments: cell index, pointer to pdsp:Sequence, behavior (pdsp::Behavior::Loop if not given)
                engine.sequencer.sections[1].setCell(i, kick_seqs[i] );
                engine.sequencer.sections[2].setCell(i, percu_seqs[i], pdsp::Behavior::Loop);
                engine.sequencer.sections[3].setCell(i, snare_seqs[i], pdsp::Behavior::Loop);
                engine.sequencer.sections[4].setCell(i, poly_seq[i], pdsp::Behavior::Loop );
                engine.sequencer.sections[5].setCell(i, bass_seqs[i], pdsp::Behavior::Loop );
                engine.sequencer.sections[6].setCell(i, hihat_seqs[i], pdsp::Behavior::Loop );
                engine.sequencer.sections[7].setCell(i, fmpad_seqs[i], pdsp::Behavior::OneShot );
            }
            
            // synths args
            32.0f >> kick.in("pitch");
            32.0f >> kick.in("pitch_fall");
            470.0f >> kick.in("release");
            650.0f >> snare.in("noiseRelease");
            650.0f >> snare.in("release");
            0.75f >> bass.in("index");
            5.0f >> bass.in("attack");
            1600.0f >> bass.in("release");
            677.6f >> perc.in("release");
            fmsynth.env_release_ctrl.set(3553.0f);
            fmsynth.fm_ctrl.set(0.0f);
            fmsynth.self_ctrl.set(0.0f);
            fmsynth.self_mod.set(0.0f);
            fmsynth.ratio_ctrl.set(0.505f);
            
            // patching (with panning)
            kick * (dB(-6.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            kick * (dB(-6.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);
            
            perc * (dB(-3.0f) * pdsp::panL(0.25f)) >> engine.audio_out(0);
            perc * (dB(-3.0f) * pdsp::panR(0.25f)) >> engine.audio_out(1);
            
            snare * (dB(-13.5f) * pdsp::panL(-0.25f)) >> engine.audio_out(0);
            snare * (dB(-13.5f) * pdsp::panR(-0.25f)) >> engine.audio_out(1);
            
            synth.out_L() * dB(-13.5f) >> engine.audio_out(0);
            synth.out_R() * dB(-13.5f) >> engine.audio_out(1);

            synth.out_L() * dB(-27.0f) >> reverb;
            synth.out_R() * dB(-27.8f) >> reverb;
            
            bass * (dB(-12.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            bass * (dB(-12.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

            hat * (dB(-13.5f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
            hat * (dB(-13.5f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

            fmsynth.ch(0) * (dB(-7.5f) * pdsp::panL(0.0f)) >> reverb >> engine.audio_out(0);
            fmsynth.ch(1) * (dB(-7.5f) * pdsp::panR(0.0f)) >> reverb >> engine.audio_out(1);

            break;
            
            ////////////////////////////////////////////////////////////////////////////
    }
    {
    case 4:
        //////////
        // SCRAM!
        //////////
        // sequences settings
        seq_mode = 0;
        quantize = true;
        quantime = 1.0/8.0; // 1/4th

        states.resize(16);
        
        //
        // masterplan
        engine.sequencer.init( 7, 6, 112.0f); // sections, sequences, tempo
        engine.sequencer.sections[0].resizeCells(1);
        engine.sequencer.sections[0].sequence(0).label = "masterplan";
        engine.sequencer.sections[0].sequence(0).bars =  1.0 / 8.0;

        engine.sequencer.sections[0].sequence(0).code = [&] () noexcept { // masterplan sequence

            pdsp::Sequence & seq = engine.sequencer.sections[0].sequence(0); // defining variable into the lambda is fine
            // metric
            int beat = (seq.counter()) % 4;
            int bar = seq.counter() / 4;
            cout << std::to_string(bar) + ":" + std::to_string(beat) << endl;

            int index = seq.counter()%16; // we repeat the same states four time, so each pattern is 2 bars
            
            if(index == 0){  // here we generate some random numbers to select the drums cells
                //numbers to select the drums cells
                states[0] = 0; // the first state is always a kick
                for(size_t i=1; i<states.size();++i){
                    states[i] = pdsp::dice(6);
                }
            }
            
            // main flow
            if((bar == 0)&&(index % 4 == 0)) engine.sequencer.sections[1].launchCell( 0, true, seq.length());
            if((bar == 7)&&(index % 4 == 2)) engine.sequencer.sections[3].launchCell( 0, true, seq.length());
           
            if ((bar == 16)&&(index % 4 == 0)) {
                engine.sequencer.setTempo(140.0f);
                engine.sequencer.sections[4].launchCell( 0, true, seq.length());
            }
            if ((bar >=16)&&(bar <=144)) {
                engine.sequencer.sections[2].launchCell( states[index], true, seq.length());
            }
            
            // talea triple
            if (((bar >= 26)&&(bar <= 145))||((bar >= 162)&&(bar <= 226))) {
                if ((((bar == 26)||(bar+26)%17==0))&&(index % 4 == 0)) {
                    engine.sequencer.sections[5].launchCell( 0, true, seq.length());
                }
            }
            
            if (((bar >= 54)&&(bar <= 145))||((bar >= 160)&&(bar <= 227))) {
                if ((((bar == 54)||(bar+54)%56==0))&&(index % 4 == 0)) {
                    engine.sequencer.sections[5].launchCell( 1, true, seq.length());
                }
            }

            if (((bar >= 96)&&(bar <= 145))||((bar >= 160)&&(bar <= 227))) {
                if ((((bar == 96)||(bar+96)%55==0))&&(index % 4 == 0)) {
                    engine.sequencer.sections[5].launchCell( 2, true, seq.length());
                }
            }
            
            // pozo
            if ((bar == 144)&&(index % 1 == 0)) {
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
            }
            if ((bar == 236)&&(index % 4 == 0)) {
                engine.sequencer.setTempo(140.0f);
                engine.sequencer.sections[4].launchCell( 0, true, seq.length());
            }
            if ((bar >=236)&&(bar <=280)) {
                engine.sequencer.sections[2].launchCell( states[index], true, seq.length());
            }

            if ((bar == 280)&&(index % 4 == 2)) {
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                engine.sequencer.stop();
                // end //////////////////////////////////////////////////////////
            }
            
        };
        //
        
        engine.sequencer.sections[1].out_trig(0)  >> kick.in("trig");
        
        drums.add( ofToDataPath("/Users/Luigi/Documents/work/wav/MS20/unprocessed drums/kicks/wams20_kick_bouncer_u.wav") );
        drums.add( ofToDataPath("/Users/Luigi/Documents/work/wav/MS20/unprocessed drums/snares/wams20_snare_classic-heavy_u.wav") );
        drums.add( ofToDataPath("/Users/Luigi/Documents/work/wav/MS20/unprocessed drums/cymbalsSHRT/wams20_cl-hat_classic-detuned_u.wav") );
        drums.add( ofToDataPath("/Users/Luigi/Documents/work/wav/MS20/unprocessed drums/snares/wams20_snare_hard-resonance_u.wav") );
        
        engine.sequencer.sections[2].out_trig(0)  >> drums.in("trig");
        engine.sequencer.sections[2].out_value(1) >> drums.in("select");
        engine.sequencer.sections[3].out_trig(0)  >> kick2.in("trig");
        engine.sequencer.sections[4].out_trig(0)  >> perc.in("trig");
        engine.sequencer.sections[4].out_value(1)  >> perc.in("pitch");
        engine.sequencer.sections[4].out_value(2)  >> perc.in("release");
        engine.sequencer.sections[4].out_value(3)  >> perc.in("index");
        
        float o = -1.0f; // "set" negative outputs are ignored, 'o' is graphically useful
        
        // kick sequences
        kick_seqs.resize(1);
        kick_seqs[0].steplen = 1.0f/8.0f;
        kick_seqs[0].bars = 2.0f; // this can also be omitted, 1.0 is the default value
        kick_seqs[0].set( {o, 1.0f, o,o,o,o,o,o,o,o,o,o,o,o,o,o} );
        
        // drums sequence "cells"
        // first out is trigger, second is sample index select
        engine.sequencer.sections[2].sequence(0).label = "kick";
        engine.sequencer.sections[2].sequence(0).set( { { 1.0f, o   },
            { 0.0f, o } });
        engine.sequencer.sections[2].sequence(1).label = "snare";
        engine.sequencer.sections[2].sequence(1).set( { { 0.5f, o },
            { 1.0f, o } });
        engine.sequencer.sections[2].sequence(2).label = "hh";
        engine.sequencer.sections[2].sequence(2).set( { {  0.7f, 0.7f, },
            {  2.0f, 2.0f } });
        engine.sequencer.sections[2].sequence(3).label = "hh soft";
        engine.sequencer.sections[2].sequence(3).set( { {  0.5f, o },
            {  2.0f, o } } );
        engine.sequencer.sections[2].sequence(4).label = "shuffle";
        engine.sequencer.sections[2].sequence(4).set( { { 0.7f, 0.7f },
             { 2.0f, 3.0f } });
        engine.sequencer.sections[2].sequence(5).label = "hh soft";
        engine.sequencer.sections[2].sequence(5).set( { {  0.5f, o },
            {  2.0f, o } } );

        // kick2 sequences
        kick2_seqs.resize(1);
        kick2_seqs[0].steplen = 1.0f/4.0f;
        kick2_seqs[0].bars = 3.0f; // this can also be omitted, 1.0 is the default value
        kick2_seqs[0].set( {1.0,o,o,o,o,o,o,o,o,o,o,o} );

        // percu sequences
        percu_seqs.resize(1);
        // lambda love
        percu_seqs[0].code = [&] () noexcept { // better to tag noexcept for code used by the DSP engine
            pdsp::Sequence & seq = percu_seqs[0]; // reference
            
            seq.steplen = 1.0/16.0;
            seq.begin();
            for (int i=0; i<16; ++i){
                float trig = (pdsp::dice(24.0f)<=1.0f) ? 1.0f : -1.0f;
                seq.message( double(i),       trig,  0 );
                if (trig == 1.0f) {
                    float pitch = pdsp::dice(24.0f,110.0f);
                    float release = pdsp::dice(320.0f,680.0f);
                    float index = pdsp::dice(1.0f,100.0f);
                    seq.message( double(i), pitch,  1 );
                    seq.message( double(i), release,2 );
                    seq.message( double(i), index,  3 );
                }
            }
            seq.end();
        };
        
        // karplus seqs
        poly_seq.resize(5);
        poly_seq[0].steplen = 1.0f/2.0f;
        poly_seq[0].bars = 8.5f;
        poly_seq[0].set( { { 1.0f,o,o,o,  o,o,o,o,  o,o,o,0.0f }, //trigs
                           { 54.0f,o,o,o, o,o,o,o,  o,o,o,o}   });
        
        
        poly_seq[1].steplen = 1.0f/2.0f;
        poly_seq[1].bars = 11.0f;
        poly_seq[1].set( { { 1.0f,o,o,o,  o,o,o,o,  o,o,o,o, o,o,o,0.0f}, //trigs
                           { 54.0f,o,o,o, o,o,o,o,  o,o,o,o, o,o,o,o},
                           { 1.0f,o,o,o,  o,o,o,o,  o,o,o,o, o,o,o,0.0f}, //trigs
                           { 55.0f,o,o,o, o,o,o,o,  o,o,o,o, o,o,o,o}    });
        
        poly_seq[2].steplen = 1.0f/2.0f;
        poly_seq[2].bars = 8.5f;
        poly_seq[2].set( { { 1.0f,o,o,o,  o,o,o,o,  o,o,o,0.0f }, //trigs
            { 58.0f,o,o,o, o,o,o,o,  o,o,o,o}   });
        
        karplus.setup( 2  );
        
        for ( size_t i = 0; i<2; ++i ){
            engine.sequencer.sections[5].out_trig( i*2 ) >> karplus.in_trig(i);
            engine.sequencer.sections[5].out_value( i*2 + 1 ) >> karplus.in_pitch(i);
        }
        
        // assigning the sequences to the sequencer sections
        for(int i = 0; i<5; ++i){
            // arguments: cell index, pointer to pdsp:Sequence, behavior (pdsp::Behavior::Loop if not given)
            engine.sequencer.sections[1].setCell(i, kick_seqs[i] );
            engine.sequencer.sections[3].setCell(i, kick2_seqs[i] );
            engine.sequencer.sections[4].setCell(i, percu_seqs[i] );
            engine.sequencer.sections[5].setCell(i, poly_seq[i],pdsp::Behavior::OneShot );
        }
        
        // synths args
        30.0f >> kick.in("pitch");
        30.0f >> kick.in("pitch_fall");
        3370.0f >> kick.in("release");
        33.0f >> kick2.in("pitch");
        33.0f >> kick2.in("pitch_fall");
        3370.0f >> kick2.in("release");
        // fx args
        1.5f >> reverb.in_time();
        filter.modeControl.set(4.0f);
        filter.cutoffControl.set(84.0f);
        filter.resoControl.set(0.0f);

        //delay.lDelayTimeControl.set(4.0f);
        //delay.rDelayTimeControl.set(6.0f);
        
        // patching (with panning)
        kick * (dB(-3.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        kick * (dB(-3.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        kick2 * (dB(-3.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        kick2 * (dB(-3.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        drums * dB(-3.0f) >> filter >> engine.audio_out(0);
        drums * dB(-3.0f) >> filter >> engine.audio_out(1);

        perc * dB(0.0f) >> engine.audio_out(0);
        perc * dB(0.0f) >> engine.audio_out(1);

        karplus.ch(0) * dB(-15.0f) >> engine.audio_out(0);
        karplus.ch(1) * dB(-15.0f) >> engine.audio_out(1);
        karplus.ch(0) * dB(-4.5f) >> delay.ch(0) >> engine.audio_out(0);
        karplus.ch(1) * dB(-4.5f) >> delay.ch(1) >> engine.audio_out(1);
        karplus.ch(0) * dB(-4.5f) >> reverb.ch(0) >> engine.audio_out(0);
        karplus.ch(1) * dB(-4.5f) >> reverb.ch(1) >> engine.audio_out(1);

        break;
        
    }
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    {
        case 5:
        //////////
        // self-simulation
        //////////
        
        angel.load("/Users/Luigi/Documents/work/wav/samples/angel1.wav");
        drone.setup(0,0);
        drone.addSample(angel);
        // sequences settings
        seq_mode = 0;
        quantize = true;
        quantime = 1.0/8.0; // 1/4th
        
        //
        // masterplan
        engine.sequencer.init( 7, 5, 131.0f); // sections, sequences, tempo
        engine.sequencer.sections[0].resizeCells(1);
        engine.sequencer.sections[0].sequence(0).label = "masterplan";
        engine.sequencer.sections[0].sequence(0).bars =  1.0 / 8.0;
        
        engine.sequencer.sections[0].sequence(0).code = [&] () noexcept { // masterplan sequence
            pdsp::Sequence & seq = engine.sequencer.sections[0].sequence(0); // defining variable into the lambda is fine
            // metric
            int beat = (seq.counter()) % 4;
            int bar = seq.counter() / 4;
            cout << std::to_string(bar) + ":" + std::to_string(beat) << endl;

            // main flow
            if((bar == 0)&&(beat  == 0)) engine.sequencer.sections[1].launchCell( 0, true, seq.length());
            if((bar == 4)&&(beat  == 0)) engine.sequencer.sections[4].launchCell( 0, true, seq.length());
            if((bar == 11)&&(beat  == 3)) engine.sequencer.sections[2].launchCell( 0, true, seq.length());
            if((bar == 12)&&(beat  == 0)) engine.sequencer.sections[3].launchCell( 0, true, seq.length());
            if((bar == 28)&&(beat  == 1)) {
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                drone.ch(0) * dB(droneGain) >> compre.ch(0);drone.ch(1) * dB(droneGain) >> compre.ch(1);
                drone.positionControl.set(0.94f);
            }
            if((bar >= 28)&&(bar <= 36)) {
                droneGain += 0.5f;
                drone.ch(0) * dB(droneGain) >> compre.ch(0);drone.ch(1) * dB(droneGain) >> compre.ch(1);
                drone.ch(0) * dB(droneGain) >> delay.ch(0);drone.ch(1) * dB(droneGain) >> delay.ch(1);

            }
            if((bar == 44)&&(beat  == 1)) {
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                droneGain = -30.0f;
                drone.ch(0) * dB(droneGain) >> compre.ch(0);drone.ch(1) * dB(droneGain) >> compre.ch(1);
                drone.ch(0) * dB(droneGain) >> delay.ch(0);drone.ch(1) * dB(droneGain) >> delay.ch(1);
                delay.lFeedbackControl.set(1.0f);delay.rFeedbackControl.set(1.0f);
            }
                if(bar == 50) {
                    if (beat == 0) {
                        engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                    }
                    if (beat == 1) {
                        engine.sequencer.sections[4].launchCell( 0, true, seq.length());
                }
            }
            if((bar == 57)&&(beat  == 3)) engine.sequencer.sections[2].launchCell( 0, true, seq.length());
            if((bar == 58)&&(beat  == 0)) engine.sequencer.sections[3].launchCell( 0, true, seq.length());
            if((bar == 66)&&(beat  == 0)) engine.sequencer.sections[5].launchCell( 0, true, seq.length());
            if(bar == 98) {
                droneGain = -3.0f;
                drone.ch(0) * dB(droneGain) >> compre.ch(0);drone.ch(1) * dB(droneGain) >> compre.ch(1);
                drone.ch(0) * dB(-60.0f) >> delay.ch(0);drone.ch(1) * dB(-60.0f) >> delay.ch(1);
                drone.positionControl.set(0.9f);drone.densityControl.set(0.15f);
                delay.lFeedbackControl.set(0.85f);delay.rFeedbackControl.set(0.85f);
            }
            if((bar == 106)&&(beat == 0)) engine.sequencer.sections[4].launchCell( 0, true, seq.length());
            if((bar == 122)&&(beat  == 1)) {
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
            }
            if (bar == 128) {
                droneGain = -60.0f;
                delay.lFeedbackControl.set(0.5f);delay.rFeedbackControl.set(0.5f);
                delay.lDelayTimeControl.set(5);delay.rDelayTimeControl.set(3);
                delay.ch(0) * dB(8.5f) >> engine.audio_out(0);delay.ch(1) * dB(8.5f) >> engine.audio_out(1);
            }
            if ((bar == 131)&&(beat  == 2)) engine.sequencer.sections[5].launchCell( -1, true, seq.length());

            if((bar >= 128)&&(bar <= 140)) {
                droneGain += 1.0f;
                snare * dB(droneGain) >> delay.ch(0);snare * dB(droneGain) >> delay.ch(1);
            }
            if((bar >= 148)&&(bar <= 151)) {
                engine.sequencer.sections[4].launchCell( 0, true, seq.length());
            }
            if(bar == 152) {
                drone.ch(0) * dB(-6.0f) >> delay.ch(0);drone.ch(1) * dB(-6.0f) >> delay.ch(1);
                if(beat  == 0) {
                engine.sequencer.sections[1].launchCell( 0, true, seq.length());
                }
                if (beat  == 1) {
                engine.sequencer.sections[4].launchCell( 0, true, seq.length());
                }
            }
            if(bar == 155) {
                 drone.ch(0) * dB(-60.0f) >> delay.ch(0);drone.ch(1) * dB(-60.0f) >> delay.ch(1);
                 drone.ch(0) * dB(-60.0f) >> compre.ch(0);drone.ch(1) * dB(-60.0f) >> compre.ch(1);
            }
            if((bar == 158)&&(beat == 3)) engine.sequencer.sections[2].launchCell( 0, true, seq.length());
            if((bar == 160)&&(beat == 0)) engine.sequencer.sections[3].launchCell( 0, true, seq.length());
            if((bar == 168)&&(beat == 0)) engine.sequencer.sections[5].launchCell( 0, true, seq.length());
            if((bar == 184)&&(beat == 0)) engine.sequencer.sections[6].launchCell( 0, true, seq.length());
            if (bar == 264) {
                drone.ch(0) * dB(0.0f) >> compre.ch(0);drone.ch(1) * dB(0.0f) >> compre.ch(1);
                drone.positionControl.set(0.94f);
            }
            if (bar == 304) {
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
            }
            if((bar == 318)&&(beat == 3)) engine.sequencer.sections[2].launchCell( 0, true, seq.length());
            if((bar == 324)&&(beat == 0)) {
                engine.sequencer.sections[1].launchCell( 0, true, seq.length());
            }
            if((bar == 344)&&(beat == 0)) {
                engine.sequencer.sections[2].launchCell( 0, true, seq.length());
                engine.sequencer.sections[3].launchCell( 0, true, seq.length());
                engine.sequencer.sections[4].launchCell( 0, true, seq.length());
            }
            if (bar == 384) {
                drone.ch(0) * dB(-6.0f) >> delay.ch(0);drone.ch(1) * dB(-6.0f) >> delay.ch(1);
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
            }
            if (bar == 386) {
                drone.ch(0) * dB(-60.0f) >> delay.ch(0);drone.ch(1) * dB(-60.0f) >> delay.ch(1);
                drone.ch(0) * dB(-60.0f) >> compre.ch(0);drone.ch(1) * dB(-60.0f) >> compre.ch(1);
            }
            if ((bar == 396)&&(beat  == 2)) engine.sequencer.sections[5].launchCell( -1, true, seq.length());
            if ((bar == 403)&&(beat  == 3)) engine.sequencer.stop();
            ////////////////////////////////////////////////end
            ///////////////////////////////////////////////////
        };
        
        // routing
        engine.sequencer.sections[1].out_trig(0)  >> kick.in("trig");
        engine.sequencer.sections[2].out_trig(0)  >> snare.in("trig");
        engine.sequencer.sections[3].out_trig(0)  >> hat.in("trig");
        engine.sequencer.sections[3].out_value(1)  >> hat.in("release");
        engine.sequencer.sections[4].out_trig(0)  >> bass.in("trig");
        engine.sequencer.sections[4].out_value(1)  >> bass.in("pitch");
        
        fmsynth.setup(3);
        
        for ( size_t i = 0; i<3; ++i ){
            engine.sequencer.sections[5].out_trig( i*2 ) >> fmsynth.voices[i].in("trig");
            engine.sequencer.sections[5].out_value( i*2 + 1 ) >> fmsynth.voices[i].in("pitch");
        }

        fmsynth2.setup(1);
        engine.sequencer.sections[6].out_trig(0) >> fmsynth2.voices[0].in("trig");
        engine.sequencer.sections[6].out_value(1) >> fmsynth2.voices[0].in("pitch");

        float o = -1.0f; // "set" negative outputs are ignored, 'o' is graphically useful
        
        // kick sequences
        kick_seqs.resize(1);
        kick_seqs[0].steplen = 1.0/16.0;
        kick_seqs[0].bars = 2.0; // this can also be omitted, 1.0 is the default value
        kick_seqs[0].set( {1.0f,o,o,o, 1.0f,o,o,o, 1.0f,o,o,o, 1.0f,o,o,o,1.0f,o,o,o, 1.0f,o,o,o, 1.0f,o,o,o, 1.0f,o,o,1.0f
        } );
        
        // snare seqs
        snare_seqs.resize(1);
        snare_seqs[0].steplen = 1.0f/16.0f;
        snare_seqs[0].bars = 1.0f/2.0f; // this can also be omitted, 1.0 is the default value
        snare_seqs[0].set( {o, o,o, o, 1.0f, o,o,o} );
        
        // hihat sequences
        hihat_seqs.resize(2);
        hihat_seqs[0].steplen = 1.0f/32.0f;
        hihat_seqs[0].bars = 1.0f/4.0f; // this can also be omitted, 1.0 is the default value
        hihat_seqs[0].set( {{1.0f,o,0.5f,o,0.75f,o,0.5f,o},
                            {65.6f,o,111.1f,o,65.6f,o,111.1f,o}} );
        
        hihat_seqs[1].steplen = 1.0f/64.0f;
        hihat_seqs[1].bars = 1.0f/8.0f; // this can also be omitted, 1.0 is the default value
        hihat_seqs[1].set( {{1.0f,o,0.5f,o,0.75f,o,0.5f,o},
            {65.6f,o,111.1f,o,65.6f,o,111.1f,o}} );
        
        // bass sequences
        bass_seqs.resize(1);
        bass_seqs[0].steplen = 1.0f/16.0f;
        bass_seqs[0].bars = 2.0f;
        bass_seqs[0].set( {
            {1.0f, 0.0f,o,o, o, o,o,1.0f,0.0f, 1.0f, 0.0f,o, o, o,1.0f,0.0f,
             1.0f, 0.0f,o,o, o, o,o,1.0f,0.0f, 1.0f, 0.0f,o, o, o,1.0f,1.0f
            }, //trigs
            {29.0f,o,o,o,o,o,o,29.0f,o, 31.0f,o,o,o,o,27.0f,o,
             29.0f,o,o,o,o,o,o,29.0f,o, 36.0f,o,o,o,o,27.0f,28.0f
            } });//pitch
        
        // piano fm
        fmpad_seqs.resize(1);
        fmpad_seqs[0].steplen = 1.0f/16.0f;
        fmpad_seqs[0].bars = 66.0f/16.0f;
        fmpad_seqs[0].set( {
            {1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,o,o,
             1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,1.0f,0.0f,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,o,o,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,1.0f,0.0f,o,o
            }, //trigs
            {76.0f,o,o,o,    o,o,78.0f,o,     o,o,80.0f,o,    o,o,o,o,
             76.0f,o,o,o,    o,o,78.0f,o,     o,o,80.0f,o,    o,o,76.0f,o,
                76.0f,o,o,o,    o,o,78.0f,o,     o,o,80.0f,o,    o,o,o,o,
                76.0f,o,o,o,    o,o,78.0f,o,     o,o,80.0f,o,    o,o,76.0f,o,o,o
            },  //pitch
            
            {1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,o,o,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,1.0f,0.0f,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,o,o,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,1.0f,0.0f,o,o
            }, //trigs
            {73.0f,o,o,o,    o,o,73.0f,o,     o,o,72.0f,o,    o,o,o,o,
                73.0f,o,o,o,    o,o,73.0f,o,     o,o,72.0f,o,    o,o,73.0f,o,
                73.0f,o,o,o,    o,o,73.0f,o,     o,o,72.0f,o,    o,o,o,o,
                73.0f,o,o,o,    o,o,73.0f,o,     o,o,72.0f,o,    o,o,73.0f,o,o,o
            },  //pitch
            
            {1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,o,o,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,1.0f,0.0f,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,o,o,
                1.0f,0.0f,o,o,  o,o,1.0f,0.0f,   o,o,1.0f,0.0f,  o,o,1.0f,0.0f,o,o
            }, //trigs
            {71.0f,o,o,o,    o,o,71.0f,o,     o,o,69.0f,o,    o,o,o,o,
                71.0f,o,o,o,    o,o,71.0f,o,     o,o,69.0f,o,    o,o,71.0f,o,
                71.0f,o,o,o,    o,o,71.0f,o,     o,o,69.0f,o,    o,o,o,o,
                71.0f,o,o,o,    o,o,71.0f,o,     o,o,69.0f,o,    o,o,71.0f,o,o,o
            }  //pitch

        });

        // nice string
        poly_seq.resize(1);
        poly_seq[0].steplen = 1.0f/2.0f;
        poly_seq[0].bars = 10.0f;
        poly_seq[0].set( {
            {1.0f,o,o,o, o,o,o,o,  o,o,o,o, o,o,o,o, o,o,o,0.0f}, //trigs
            {90.0f,o,o,o,o,o,  85.0f,o,o,o,o,o,  87.0f,o,o,o,o,o,o,o},  //pitch
        });
        
        // assigning the sequences to the sequencer sections
        for(int i = 0; i<2; ++i){
            // arguments: cell index, pointer to pdsp:Sequence, behavior (pdsp::Behavior::Loop if not given)
            engine.sequencer.sections[1].setCell(i, kick_seqs[i] );
            engine.sequencer.sections[2].setCell(i, snare_seqs[i] );
            engine.sequencer.sections[3].setCell(i, hihat_seqs[i] );
            engine.sequencer.sections[4].setCell(i, bass_seqs[i] );
            engine.sequencer.sections[5].setCell(i, fmpad_seqs[i] );
            engine.sequencer.sections[6].setCell(i, poly_seq[i] );
        }
        
        // synths args
        26.0f >> kick.in("pitch");
        26.0f >> kick.in("pitch_fall");
        383.0f >> kick.in("release");
        0.15f >> bass.in("index");
        4.0f >> bass.in("attack");
        898.0f >> bass.in("release");
        1.0f >> bass.in("ratio");
        77.7f >> snare.in("noiseRelease");
        2.5f >> perc.in("ratio");
        444.0f >> perc.in("release");
        drone.densityControl.set(0.1f);
        drone.smoothing(0.0f);
        drone.positionControl.set(0.95f);
        fmsynth.fm_ctrl.set(0.1f);
        fmsynth.self_ctrl.set(0.0f);
        fmsynth.self_mod.set(0.02f);
        fmsynth.ratio_ctrl.set(0.5f);
        fmsynth.env_attack_ctrl.set(0.3f);
        fmsynth.env_release_ctrl.set(333.3f);
        // fm 2
        fmsynth2.fm_ctrl.set(0.1f);
        fmsynth2.self_mod.set(0.3f);
        fmsynth2.ratio_ctrl.set(1.01f);
        fmsynth2.env_attack_ctrl.set(222.2f);
        fmsynth2.env_release_ctrl.set(1777.1f);
        
        // fx args
        0.5f >> reverb.in_time();
        0.85f >> reverb2.in_density();
        
        // patching (with panning)
        kick * (dB(-6.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        kick * (dB(-6.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        snare * (dB(-12.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        snare * (dB(-12.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        hat * (dB(-10.5f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        hat * (dB(-10.5f) * pdsp::panR(0.0f)) >> engine.audio_out(1);
        
        bass * (dB(-10.5f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        bass * (dB(-10.5f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        drone.ch(0) * dB(-60.0f) >> compre.ch(0) >> engine.audio_out(0);
        drone.ch(1) * dB(-60.0f) >> compre.ch(1) >> engine.audio_out(1);
        
        fmsynth.ch(0) * dB(-22.5f) >> engine.audio_out(0);
        fmsynth.ch(1) * dB(-22.5f) >> engine.audio_out(1);
        fmsynth.ch(0) * dB(-22.5f) >> reverb >> engine.audio_out(0);
        fmsynth.ch(1) * dB(-22.5f) >> reverb >> engine.audio_out(1);

        fmsynth2.ch(0) * dB(-27.0f) >> reverb2 >> engine.audio_out(0);
        fmsynth2.ch(1) * dB(-27.0f) >> reverb2 >> engine.audio_out(1);

        delay.ch(0) * dB(21.0f) >> engine.audio_out(0);
        delay.ch(1) * dB(21.0f) >> engine.audio_out(1);
        break;
    }
    {
        case 6:
        //////////
        // LAST EXIT
        //////////
        // sequences settings
        seq_mode = 0;
        quantize = true;
        quantime = 1.0/8.0; // 1/4th
        
        //
        // masterplan
        engine.sequencer.init( 5, 6, 128.0f); // sections, sequences, tempo
        engine.sequencer.sections[0].resizeCells(1);
        engine.sequencer.sections[0].sequence(0).label = "masterplan";
        engine.sequencer.sections[0].sequence(0).bars =  1.0 / 8.0;
        
        engine.sequencer.sections[0].sequence(0).code = [&] () noexcept { // masterplan sequence
            
            pdsp::Sequence & seq = engine.sequencer.sections[0].sequence(0); // defining variable into the lambda is fine

            int beat = (seq.counter()/2) % 4;
            int bar = seq.counter() / 8;
            cout << std::to_string(bar+totalbar) + ":" + std::to_string(beat) << endl;
            
            // main flow
            int _2bar = seq.counter()%16;

            if(_2bar % 4 == 0) {
                engine.sequencer.sections[1].launchCell( 0, true, seq.length());
            }
            if(_2bar % 16 == 0) {
                engine.sequencer.sections[2].launchCell( 1, true, seq.length());
            }
            
            /*
            // organ
            if(_2bar % 16 == downOrgan) {
                int w = pdsp::dice(6);
                engine.sequencer.sections[4].launchCell( w, true, seq.length());
            }
            */
            
            // bass
            // formal ratios 7/0 - 8/0 - 5/0 - 11/0               10/0  - 15/0 - --------- 12/0 -9/0 - 13/0
            if(bar+totalbar == 8) {
                modBass = 7;downBeat = 0;
            }
            if(bar+totalbar == 16) {
                modBass = 8;downBeat = 0;organ = 1;
            }
            if(bar+totalbar == 24) {
                modBass = 11;downBeat = 0;organ = 2;
            }
            if(bar+totalbar == 32) {
                organ = 0;
            }
            if(bar+totalbar == 40) {
                modBass = 7;downBeat = 0;
            }
            if(bar+totalbar == 48) {
                modBass = 8;downBeat = 0;organ = 1;
            }
            if(bar+totalbar == 56) {
                modBass = 11;downBeat = 0;organ = 4;
            }
            if(bar+totalbar == 64) {
                organ = 0;
            }
            if(bar+totalbar == 72) {
                modOrgan = 1;
            }
            if((bar+totalbar >= 72)&&(bar+totalbar <= 87)) {
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
            }
            if((bar+totalbar == 72)&&(_2bar % 2 == 1)) {
                downBeat = 1111;
            }
            if(bar+totalbar == 74) {
                downBeat = 0;modBass = 8;
                if(_2bar % 2 == 1) {
                    downBeat = 1111;
                }
            }
            if(bar+totalbar == 76) {
                downBeat = 0;modBass = 8;
                if(_2bar % 2 == 1) {
                    downBeat = 1111;
                }
            }
            if(bar+totalbar == 78) {
                downBeat = 0;modBass = 8;
                if(_2bar % 2 == 1) {
                    downBeat = 1111;
                }
            }
            if(bar+totalbar == 80) {
                downBeat = 0;modBass = 8;
            }
            if(bar+totalbar == 84) {
                modBass = 4;
            }
            if(bar+totalbar == 86) {
                modBass = 2;
            }
            if(bar+totalbar == 87) {
                modBass = 1;
            }
            if(bar+totalbar == 88) {
                modBass = 7;modOrgan = 16;organ = 4;
            }
            if((bar+totalbar >= 88)&&(bar+totalbar <= 109)&&(_2bar % 16 == 0)) {
                organ = (pdsp::dice(3)<=1) ? 4 : 2;
            }
            if(bar+totalbar == 96) {
                modBass = 8;downBeat = 0;
            }
            if(bar+totalbar == 104) {
                modBass = 11;downBeat = 0;
            }
            if(bar+totalbar == 111) {
                organ = 2;
            }
            if(bar+totalbar == 112) {
                organ = 0;
            }
            if((bar+totalbar >= 120)&&(bar+totalbar <= 127)) {
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
            }
            if((bar+totalbar == 120)&&(_2bar % 2 == 1)) {
                downBeat = 1111;modOrgan= 1;
            }
            //
            
            if(_2bar % modBass == downBeat) {
                engine.sequencer.sections[3].launchCell( 0, true, seq.length());
            }
            
            // organ
            if(_2bar % modOrgan == 0) {
                engine.sequencer.sections[4].launchCell( organ, true, seq.length());
            }
            
            // trastavilla
            if(((bar+totalbar == 7)||(bar+totalbar == 23)||(bar+totalbar == 39)||(bar+totalbar == 55)||(bar+totalbar == 87)||(bar+totalbar == 103))&&(_2bar == 14)) {
                engine.sequencer.sections[2].launchCell( -1, true, seq.length());
                engine.sequencer.sections[3].launchCell( -1, true, seq.length());
                engine.sequencer.sections[4].launchCell( -1, true, seq.length());
                engine.sequencer.sections[1].launchCell( -1, true, seq.length());
                engine.sequencer.sections[0].launchCell( 0, true, seq.length());
                totalbar += (bar+1);
            }
            if((bar+totalbar == 143)&&(beat == 3)&&(_2bar % 2 == 0)) {
                engine.sequencer.stop();
                // end
                //////////////////////////////
            }
        };
             
        //
        
        engine.sequencer.sections[1].out_trig(0)  >> kick.in("trig");
        engine.sequencer.sections[2].out_trig(0)  >> hat.in("trig");
        engine.sequencer.sections[2].out_value(1)  >> hat.in("release");
        engine.sequencer.sections[3].out_trig(0)  >> bass.in("trig");
        engine.sequencer.sections[3].out_value(1)  >> bass.in("pitch");
        
        fmsynth.setup(4);
        
        for ( size_t i = 0; i<4; ++i ){
            engine.sequencer.sections[4].out_trig( i*2 ) >> fmsynth.voices[i].in("trig");
            engine.sequencer.sections[4].out_value( i*2 + 1 ) >> fmsynth.voices[i].in("pitch");
        }
        float o = -1.0f; // "set" negative outputs are ignored, 'o' is graphically useful
        
        // kick sequences
        kick_seqs.resize(1);
        kick_seqs[0].steplen = 1.0/4.0;
        kick_seqs[0].bars = 1.0/4.0; // this can also be omitted, 1.0 is the default value
        kick_seqs[0].set( {1.0f} );

        // hihat sequences
        hihat_seqs.resize(2);
        hihat_seqs[0].steplen = 1.0/8.0;
        hihat_seqs[0].bars = 1.0/4.0; // this can also be omitted, 1.0 is the default value
        hihat_seqs[0].set( {{o,1.0f},{o,120.0f}} );

        hihat_seqs[1].steplen = 1.0/16.0;
        hihat_seqs[1].bars = 2.0; // this can also be omitted, 1.0 is the default value
        hihat_seqs[1].set( {{o,o,1.0f,o,o,o,1.0f,o,o,o,1.0f,o,o,o,1.0f,o,
                             o,o,1.0f,o,o,o,1.0f,o,o,o,1.0f,o,o,o,o,1.0f},
                           {o,o,120.0f,o,o,o,120.0f,o,o,o,120.0f,o,o,o,120.0f,o,
                            o,o,120.0f,o,o,o,120.0f,o,o,o,120.0f,o,o,o,o,120.0f}} );
        // bass sequences
        bass_seqs.resize(1);
        bass_seqs[0].steplen = 1.0/8.0;
        bass_seqs[0].bars = 2.0f;
        bass_seqs[0].set( {
            {1.0f, 0.0f,o,o, o, o,1.0f,0.0f}, //trigs
            {38.0f,o,o,o,o,o,41.0f,o} });//pitch
        
        // house organ
        fmpad_seqs.resize(6);
        fmpad_seqs[0].bars = 2.0f;
        fmpad_seqs[0].steplen = 1.0f/4.0f;
        fmpad_seqs[0].set( { { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 62.0f,o,o,o,o,o,o,62.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, o, 1.0f }, //trigs
            { 65.0f,o,o,o,o,o,o,65.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, o, 1.0f }, //trigs
            { 69.0f,o,o,o,o,o,o,67.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, o, 1.0f }, //trigs
            { 72.0f,o,o,o,o,o,o,71.0f}});

        fmpad_seqs[1].bars = 1.0f;
        fmpad_seqs[1].steplen = 1.0f/8.0f;
        fmpad_seqs[1].set( { { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 62.0f,o,o,o,o,o,o,62.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 65.0f,o,o,o,o,o,o,65.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 69.0f,o,o,o,o,o,o,67.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f}, //trigs
            { 72.0f,o,o,o,o,o,o,71.0f}});
        
        fmpad_seqs[2].bars = 2.0f;
        fmpad_seqs[2].steplen = 1.0f/4.0f;
        fmpad_seqs[2].set( { { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 65.0f,o,o,o,o,o,o,65.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 69.0f,o,o,o,o,o,o,67.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f}, //trigs
            { 72.0f,o,o,o,o,o,o,71.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f}, //trigs
            { 76.0f,o,o,o,o,o,o,74.0f}});
        
        fmpad_seqs[3].bars = 1.0f;
        fmpad_seqs[3].steplen = 1.0f/8.0f;
        fmpad_seqs[3].set( { { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 65.0f,o,o,o,o,o,o,65.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 69.0f,o,o,o,o,o,o,67.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 72.0f,o,o,o,o,o,o,71.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 76.0f,o,o,o,o,o,o,74.0f}});

        fmpad_seqs[4].bars = 2.0f;
        fmpad_seqs[4].steplen = 1.0f/4.0f;
        fmpad_seqs[4].set( { { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 65.0f,o,o,o,o,o,o,65.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 69.0f,o,o,o,o,o,o,71.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 72.0f,o,o,o,o,o,o,74.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 76.0f,o,o,o,o,o,o,79.0f}});

        fmpad_seqs[5].bars = 1.0f;
        fmpad_seqs[5].steplen = 1.0f/8.0f;
        fmpad_seqs[5].set( { { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 65.0f,o,o,o,o,o,o,65.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 69.0f,o,o,o,o,o,o,71.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 72.0f,o,o,o,o,o,o,74.0f},
            { 1.0f,  o,  o,  o,  o,  o, o, 1.0f }, //trigs
            { 76.0f,o,o,o,o,o,o,79.0f}});
  
        // assigning the sequences to the sequencer sections
        for(int i = 0; i<6; ++i){
            // arguments: cell index, pointer to pdsp:Sequence, behavior (pdsp::Behavior::Loop if not given)
            engine.sequencer.sections[1].setCell(i, kick_seqs[i] );
            engine.sequencer.sections[2].setCell(i, hihat_seqs[i] );
            engine.sequencer.sections[3].setCell(i, bass_seqs[i] );
            engine.sequencer.sections[4].setCell(i, fmpad_seqs[i] );
        }
        
        // synths args
        31.0f >> kick.in("pitch");
        31.0f >> kick.in("pitch_fall");
        370.0f >> kick.in("release");
        0.4f >> bass.in("index");
        10.0f >> bass.in("attack");
        141.0f >> bass.in("release");
        fmsynth.fm_ctrl.set(0.125f);
        fmsynth.self_ctrl.set(0.0f);
        fmsynth.self_mod.set(0.0f);
        fmsynth.ratio_ctrl.set(1.0f);
        fmsynth.env_release_ctrl.set(999.9f);
        // FX
        filter.cutoffControl.set(78.0f);
        filter.modeControl.set(1.0f);
        filter2.cutoffControl.set(78.0f);
        filter2.modeControl.set(0.0f);

        // patching (with panning)
        kick * (dB(-9.0f) * pdsp::panL(0.0f))  >> filter >> engine.audio_out(0);
        kick * (dB(-9.0f) * pdsp::panR(0.0f))  >> filter >> engine.audio_out(1);
        
        hat * (dB(-9.0f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        hat * (dB(-9.0f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        bass * (dB(-6.0f) * pdsp::panL(0.0f))  >> engine.audio_out(0);
        bass * (dB(-6.0f) * pdsp::panR(0.0f))  >> engine.audio_out(1);
 
        fmsynth.ch(0) * (dB(-24.75f) * pdsp::panL(0.0f)) >> engine.audio_out(0);
        fmsynth.ch(1) * (dB(-24.75f) * pdsp::panR(0.0f)) >> engine.audio_out(1);

        break;
    }
 }
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
    
}
