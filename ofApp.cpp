#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);

	this->font_size = 20;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.load(font_settings);

	this->words = {

		"H", "A", "P", "P", "Y", 
		"N", "E", "W",
		"Y", "E", "A", "R"
	};

	for (int x = this->font_size * -15; x <= this->font_size * 15; x += this->font_size * 0.8) {

		for (int y = this->font_size * -15; y <= this->font_size * 15; y += this->font_size * 1.2) {

			this->location_list.push_back(glm::vec2(x - this->font_size * 0.2, y - this->font_size * 0.5));
			this->index_list.push_back(0.f);
			this->param_list.push_back(true);
		}
	}


}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (auto& param : this->param_list) {

		param = false;
	}

	for (int k = 0; k < 2; k++) {

		auto noise_seed = ofRandom(1000);
		for (int x = -720; x <=720; x += 3) {

			auto y = ofMap(ofNoise(noise_seed, x * 0.0005 + ofGetFrameNum() * 0.01), 0, 1, -350, 350);
			for (int i = 0; i < this->location_list.size(); i++) {

				auto distance = glm::distance(glm::vec2(x, y), this->location_list[i]);
				if (distance < this->font_size * 0.8) {

					this->index_list[i] += 1;

					this->index_list[i] = (int)this->index_list[i] % this->words.size();
					this->param_list[i] = true;
				}

				distance = glm::distance(glm::vec2(x, -y), this->location_list[i]);
				if (distance < this->font_size * 0.8) {

					this->index_list[i] += 1;
					
					this->index_list[i] = (int)this->index_list[i] % this->words.size();
					this->param_list[i] = true;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->location_list.size(); i++) {

		ofColor location_color;
		location_color.setHsb(ofRandom(255), 150, 255);

		if (this->param_list[i]) {

			ofSetColor(location_color);
		}
		else {

			ofSetColor(96);
		}

		this->font.drawString(this->words[this->index_list[i]], this->location_list[i].x, this->location_list[i].y);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}