#include "MainScene.h"

void MainScene::LoadData() {
	if (std::filesystem::exists(dataFileName)) {
		xx::Data buf;
		if (int r = xx::ReadAllBytes(dataFileName, buf)) {
			throw std::logic_error(xx::ToString("xx::ReadAllBytes(dataFileName = '", dataFileName, "', buf) == ", r));
		}

		if (int r = oh.ReadFrom(buf, data)) {
			throw std::logic_error(xx::ToString("oh.ReadFrom(buf, data) == ", r));
		}
	}
}

void MainScene::SaveData() {
	xx::Data buf;
	oh.WriteTo(buf, data);
	xx::WriteAllBytes(dataFileName, buf);
}

void MainScene::editBoxReturn(cocos2d::ui::EditBox* editBox) {
	//std::string s = editBox->getText();
	//printf(s.c_str());
}
