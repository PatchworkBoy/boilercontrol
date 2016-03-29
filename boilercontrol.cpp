#include "boilercontrol.h"
#include "TransmitPin.h"
#include <stdio.h>

static const unsigned int nLongPulseLength = 868;
static const unsigned int nShortPulseLength = 250;
static const unsigned int nPauseLength = 250;
static const unsigned int nTxDelayLength = 3795;
static const unsigned int nPreTxDelay = 34120;
static const unsigned int nPostTxDelay = nPreTxDelay;

static const int ON_PACKETS[][nBitsPerPacket] = {
    {1,0,0,0,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0}
};
static const int OFF_PACKETS[][nBitsPerPacket] = {
    {1,0,0,0,1,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
    {1,1,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}
};
static const int DELAY[] = {26810, 18069, 19512, 14721, 22327, 18916, 25870, nPostTxDelay};

BoilerControl::BoilerControl(TransmitPin *transmitPin) {
    this->transmitPin = transmitPin;
}

BoilerControl::~BoilerControl() {
	delete this->transmitPin;
}

void BoilerControl::sendOnSignal() {
    printf("send ON signal\n");
    this->sendPackets(ON_PACKETS);
}

void BoilerControl::sendOffSignal() {
    printf("send OFF signal\n");
    this->sendPackets(OFF_PACKETS);
}

void BoilerControl::sendPackets(const int packets[][nBitsPerPacket]) {
    int nPacket = 0;

    this->transmitPin->pullPinLowForPeriodSync(nPreTxDelay);
    
    for(int nRepeats = 0; nRepeats < 4; nRepeats++) {
        this->sendPacket(packets[0], DELAY[nPacket]);
        nPacket++;
        this->sendPacket(packets[1], DELAY[nPacket]);
        nPacket++;
    }    

    this->transmitPin->pullPinLowForPeriodSync(nPostTxDelay);
}

void BoilerControl::sendPacket(const int packet[], const unsigned int nPostPacketDelay) {
    this->sendTxStart();

    for(int bit = 0; bit < nBitsPerPacket; bit++) {
        if(packet[bit] == 1) {
            this->send1();
        }
        else {
            this->send0();
        }
    }

    this->transmitPin->pullPinLowForPeriodSync(nPostPacketDelay);
}

void BoilerControl::sendTxStart() {
    this->transmitPin->pullPinHighForPeriodSync(nTxDelayLength);
}

void BoilerControl::send1() {
    this->sendPulse(nLongPulseLength);
}

void BoilerControl::send0() {
    this->sendPulse(nShortPulseLength);
}

void BoilerControl::sendPulse(const unsigned int nPulseLength) {
	this->transmitPin->pullPinLowForPeriodSync(nPulseLength);
	this->transmitPin->pullPinHighForPeriodSync(nPauseLength);
}
