#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "coderSynths.h"
#include "PolySynth.h"
#include "FM2.h"
#include "SampleControl.h"
#include "GrainDrone.h"
#include "MultiSampler.h"
#include "BasiVerb.h"
#include "StereoDelay.h"
#include "KarplusStrong.h"
#include "Filter.h"
#include "Compressor.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void unexCoder(int s);

    // pdsp modules
    pdsp::Engine              engine;
    pdsp::Scope               scope;
    
    // sintes
    Kick                      kick,kick2;
    FMPerc                    perc,perc2;
    HiHat                     hat;
    FMBass                    bass;
    Snare                     snare;
    PolySynth                 synth;
    np::synth::FM2            fmsynth,fmsynth2;
    Bass                      bass2;
    np::synth::GrainDrone     drone;
    MultiSampler              drums;
    np::synth::KarplusStrong  karplus;
    
    // FX
    pdsp::BasiVerb            reverb,reverb2;
    np::effect::StereoDelay   delay;
    np::effect::Filter        filter,filter2;
    np::dynamics::Compressor  compre;
    
    // samples
    np::util::SampleControl   angel;
    
    // secuencias
    std::vector<pdsp::Sequence>  kick_seqs;
    std::vector<pdsp::Sequence>  percu_seqs;
    std::vector<pdsp::Sequence>  snare_seqs;
    std::vector<pdsp::Sequence>  poly_seq;
    std::vector<pdsp::Sequence>  bass_seqs;
    std::vector<pdsp::Sequence>  hihat_seqs;
    std::vector<pdsp::Sequence>  fmpad_seqs;
    std::vector<pdsp::Sequence>  kick2_seqs;

    int                     seq_mode;
    std::atomic<bool>       quantize;
    std::atomic<double>     quantime;
    
    // outer lambda vars
    // talea index var
    std::vector<int>     states;
    int indexC = 0;
    int totalbar = 0;
    int modBass = 8;
    int downBeat = 0;
    int organ = 0;
    int modOrgan = 16;
    int downOrgan = 0;
    float droneGain = -21.0f;
};
