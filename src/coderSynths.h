//
//  coderSynths.h
//  coderSynths
//
//  Created by Luigi Tamagnini on 5/27/19.

#pragma once

#include "ofxPDSP.h"

// kick
class Kick : public pdsp::Patchable{
public:
    Kick() { patch(); }
    Kick( const Kick & other ) { patch(); }
    
    void patch (){
        //set inputs/outputs
        addModuleInput("trig", trigger_in);
        addModuleInput("pitch", pitch_in);
        addModuleInput("pitch_fall", pitch_fall);
        addModuleOutput("signal", amp );
        addModuleInput("release", release);
        pitch_in.set(48.0f);              // default
        pitch_fall.set(48.0f);                // default
        release.set(100.0f);               // default
        
        //patching
        pitch_fall >> modAmp.in_mod();
        pitch_in >> osc.in_pitch();
        release >> ampEnv.in_release();
        osc >> amp;
//        0.05f >> osc.in_fb();
        trigger_in >> ampEnv.set(3.0f, 50.0f, 100.0f) >> amp.in_mod();
        trigger_in >> modEnv.set(0.0f, 0.0f, 50.0f) >> modAmp >> osc.in_pitch();
        ampEnv.enableDBTriggering( -24.0f );
    }
private:
    pdsp::Amp           amp,modAmp;
    pdsp::FMOperator    osc;
    pdsp::AHR           ampEnv;
    pdsp::AHR           modEnv;
    pdsp::PatchNode     trigger_in;
    pdsp::PatchNode     pitch_in;
    pdsp::PatchNode     pitch_fall;
    pdsp::PatchNode     release;
};

// percu FM
class FMPerc : public pdsp::Patchable{
public:
    FMPerc() { patch(); }
    FMPerc( const FMPerc & other ) { patch(); }
    
    void patch (){
        //set inputs/outputs
        addModuleInput("trig", trigger_in);
        addModuleInput("pitch", pitch_in);
        addModuleInput("release", release);
        addModuleOutput("signal", amp );
        addModuleInput("ratio", ratio_in);
        addModuleInput("index", index_in);
        pitch_in.set(0.0f);                // default
        release.set(600.0f);               // default
        ratio_in.set(17.6f);               // default
        index_in.set(1.0f);                // default
        
        //patching
        release >> ampEnv.in_release();
        mod.out_signal() * 2.0f >> osc.in_fm();
        osc >> filter >> amp;
        trigger_in >> ampEnv.set(1.0f, 20.0f, 610.0f) >> amp.in_mod();
        pitch_in >> osc.in_pitch();
        pitch_in >> mod.in_pitch();
        ratio_in >> mod.in_ratio();
        index_in >> mod.in_fm();
        ampEnv.enableDBTriggering( -24.0f );
    }
private:
    pdsp::Amp           amp;
    pdsp::FMOperator    osc,mod;
    pdsp::AHR           ampEnv;
    pdsp::PatchNode     trigger_in;
    pdsp::PatchNode     pitch_in;
    pdsp::PatchNode     release;
    pdsp::PatchNode     ratio_in;
    pdsp::PatchNode     index_in;
    pdsp::VAFilter      filter;
};

// hihat
class HiHat : public pdsp::Patchable{
public:
    HiHat() { patch(); }
    HiHat( const HiHat & other ) { patch(); }
    
    void patch (){
        //set inputs/outputs
        addModuleInput("trig", trigger_in);
        addModuleOutput("signal", amp );
        addModuleInput("release", release);
        2.0f >> filter.in_mode();
        115.0f >> filter.in_cutoff();
        0.0f >> filter.in_reso();
        release.set(70.0f);               // default
        
        //patching
        release >> ampEnv.in_release();
        noise >> filter >> amp;
        trigger_in >> ampEnv.set(1.0f, 0.0f, 70.0f) >> amp.in_mod();
        ampEnv.enableDBTriggering( -24.0f );
    }
private:
    pdsp::Amp           amp;
    pdsp::WhiteNoise    noise;
    pdsp::VAFilter      filter;
    pdsp::AHR           ampEnv;
    pdsp::PatchNode     trigger_in;
    pdsp::PatchNode     release;
};

// bass FM
class FMBass : public pdsp::Patchable{
public:
    FMBass() { patch(); }
    FMBass( const FMBass & other ) { patch(); }
    
    void patch (){
        //set inputs/outputs
        addModuleInput("trig", trigger_in);
        addModuleInput("pitch", pitch_in);
        
        addModuleInput("attack", attack);
        addModuleInput("decay", decay);
        addModuleInput("sustain", sustain);
        addModuleInput("release", release);
        
        addModuleInput("index", index);
        addModuleInput("ratio", ratio_in);

        addModuleOutput("signal", amp );
        
        pitch_in.set(36.0f);                // default
        attack.set(1.0f);                  // default
        decay.set(200.0f);                // default
        sustain.set(0.5f);               // default
        release.set(600.0f);              // default
        index.set(2.0f);                   // default
        ratio_in.set(0.5f);                 // default
        
        //patching
        attack >> ampEnv.in_attack();
        decay >> ampEnv.in_decay();
        sustain >> ampEnv.in_sustain();
        release >> ampEnv.in_release();
        index >> modIndex.in_mod();
        //pdsp::f2p(500) >> filter.in_cutoff();
        //0.0f >> filter.in_reso();
        
        mod.out_signal() >> modIndex >> osc.in_fm();
        //osc >> filter >> amp;
        osc >> amp;
        trigger_in >> ampEnv.set(5.0f, 200.0f, 0.5f, 610.0f) >> amp.in_mod();
        pitch_in >> osc.in_pitch();
        pitch_in >> mod.in_pitch();
        ratio_in >> mod.in_ratio();
        ampEnv.enableDBTriggering( -24.0f );
    }
private:
    pdsp::Amp           amp,modIndex;
    pdsp::FMOperator    osc,mod;
    pdsp::ADSR          ampEnv;
    pdsp::PatchNode     trigger_in;
    pdsp::PatchNode     pitch_in;
    pdsp::PatchNode     attack;
    pdsp::PatchNode     decay;
    pdsp::PatchNode     sustain;
    pdsp::PatchNode     release;
    pdsp::PatchNode     index;
    pdsp::PatchNode     ratio_in;
    //pdsp::VAFilter      filter;
};

// snare
class Snare : public pdsp::Patchable{
public:
    Snare() { patch(); }
    Snare( const Snare & other ) { patch(); }
    
    void patch (){
        //set inputs/outputs
        addModuleInput("trig", trigger_in);
        addModuleOutput("signal", amp );
        addModuleInput("release", release);
        addModuleInput("tone", tone);
        addModuleInput("noiseRelease", noiseRelease);
        
        pdsp::f2p(6000.0f) >> filter.in_cutoff();
        pdsp::f2p(250.0f) >> osc.in_pitch();
        pdsp::f2p(375.0f) >> mod.in_pitch();
        
        release.set(310.0f);               // default
        tone.set(0.0f);
        noiseRelease.set(550.0f);
        
        //patching
        release >> ampEnv.in_release();
        noiseRelease >> noiseEnv.in_release();
        mod.out_triangle() * 30.0f >> osc.in_pitch();
        tone >> osc.in_pitch();
        noise >> amp2 >> filter >> amp;
        osc.out_pulse() * dB(-18.0f) >> filter;
        trigger_in >> ampEnv.set(1.0f, 0.0f, 70.0f) >> amp.in_mod();
        //trigger_in >> noiseEnv.set(1.0f, 0.0f, 70.0f) >> amp2.in_mod();
        ampEnv.enableDBTriggering( -24.0f );
    }
private:
    pdsp::Amp           amp,amp2;
    pdsp::WhiteNoise    noise;
    pdsp::VAOscillator  osc,mod;
    pdsp::VAFilter      filter;
    pdsp::AHR           ampEnv;
    pdsp::AHR           noiseEnv;
    pdsp::PatchNode     trigger_in;
    pdsp::PatchNode     release;
    pdsp::PatchNode     tone;
    pdsp::PatchNode     noiseRelease;
};

// other bass
class Bass : public pdsp::Patchable{
public:
    Bass() { patch(); }
    Bass( const Bass & other ) { patch(); }
    
    void patch (){
        //set inputs/outputs
        addModuleInput("trig", trigger_in);
        addModuleInput("pitch", osc.in_pitch());
        addModuleOutput("signal", amp );
        
        //patching
        osc.out_saw() * 2.5f >> drive >> filter >> amp;
        trigger_in >> ampEnv.set(10.0f, 50.0f, 1.0f, 555.0f) * 0.7f >> amp.in_mod();
        trigger_in >> filterEnv.set(10.0f, 120.0f, 0.0f, 555.0f) * 60.0f >> filter.in_cutoff();
        50.0f >> filter.in_cutoff();
        0.2f  >> filter.in_reso();
    }
private:
    
    pdsp::Amp           amp;
    pdsp::VAOscillator  osc;
    pdsp::VAFilter     filter;
    pdsp::ADSR          ampEnv;
    pdsp::ADSR          filterEnv;
    pdsp::Saturator1    drive;
    pdsp::PatchNode     trigger_in;
};
