#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->note.load("note.png");
	this->sound.load("Race_Car.mp3");
	this->sound.play();

	this->n_bands_to_get = 120;

	for (int j = 0; j < this->n_bands_to_get; j++) {
			this->fft_smoothed.push_back(0);
	}

	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSoundUpdate();
	float* val = ofSoundGetSpectrum(this->n_bands_to_get);

	for (int i = 0; i < this->n_bands_to_get; i++) {

		this->fft_smoothed[i] *= 0.96f;
		if (this->fft_smoothed[i] < val[i]) {

			this->fft_smoothed[i] = val[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(200);
	this->note.resize(50, 50);
	this->note.draw(ofVec2f(-(this->note.getWidth() / 2), -(this->note.getHeight() / 2)));

	if (this->sound.getIsPlaying()) {

		ofRotate(ofGetFrameNum() * 0.25);

		float radius = 80;
		for (int i = 0; i < this->n_bands_to_get; i++) {

			float deg = i * (360 / this->n_bands_to_get);
			float height = this->fft_smoothed[i] * 250 * i / 3;

			float x = radius * cos(deg * DEG_TO_RAD);
			float y = radius * sin(deg * DEG_TO_RAD);
			ofVec2f point_1(x, y);

			x = (radius + height) * cos(deg * DEG_TO_RAD);
			y = (radius + height) * sin(deg * DEG_TO_RAD);
			ofVec2f point_2(x, y);

			ofColor line_color;
			line_color.setHsb(255 - deg / 360 * 255, 255, 255);
			ofSetColor(line_color);
			ofDrawLine(point_1, point_2);
		}
	}
	
	this->cam.end();
}

//========================================================================
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}