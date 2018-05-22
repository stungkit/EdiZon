#include "gui_editor.hpp"
#include "gui_main.hpp"

#include <string>
#include <sstream>
#include <map>

GuiEditor::GuiEditor() : Gui() {
  accountInitialize();

  for(auto userID : Gui::g_currTitle->getUserIDs()) {
    struct Account account;
    accountGetProfile(&account.profile, userID);
    accountProfileGet(&account.profile, &account.userData, &account.profileBase);

    accountProfileGetImageSize(&account.profile, &account.profileImageSize);

    //TODO: Load account icon here

    //accountProfileLoadImage(&account.profile, buffer, account.profileImageSize, &account.profileImageSize);

    accounts.insert({userID, account});
  }

  accountExit();
}

GuiEditor::~GuiEditor() {

}

void GuiEditor::draw() {
  std::stringstream ss;
  ss << "Title ID: 0x" << std::hex << Gui::g_currTitle->getTitleID();

  Gui::drawRectangle(0, 0, Gui::m_framebuffer_width, Gui::m_framebuffer_height, currTheme.backgroundColor);
  Gui::drawRectangle(20, 50, Gui::m_framebuffer_width - 80, 256, currTheme.separatorColor);
  Gui::drawImage(20, 50, 256, 256, Gui::g_currTitle->getTitleIcon(), IMAGE_MODE_RGB24);
  Gui::drawText(font24, 350, 60, currTheme.textColor, Gui::g_currTitle->getTitleName().c_str());
  Gui::drawText(font20, 370, 100, currTheme.textColor, Gui::g_currTitle->getTitleAuthor().c_str());
  Gui::drawText(font20, 370, 160, currTheme.textColor, ss.str().c_str());
  Gui::drawShadow(20, 50, Gui::m_framebuffer_width - 80, 256);

  uint16_t i = 0;
  for(auto account : accounts)
    Gui::drawText(font20, 500, 500 + (i += 50), currTheme.textColor, account.second.profileBase.username);

  gfxFlushBuffers();
  gfxSwapBuffers();
  gfxWaitForVsync();
}

void GuiEditor::onInput(u32 kdown) {
  if(kdown & KEY_B)
    Gui::g_nextGui = GUI_MAIN;
}
