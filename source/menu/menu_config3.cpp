
#include "menu.hpp"

static const int g_curPage = 3;

template <class T> static inline T loopNum(T i, T s)
{
	return (i + s) % s;
}

void CMenu::_hideConfig3(bool instant)
{
	_hideConfigCommon(instant);

	if(m_current_view != COVERFLOW_GAMECUBE)
	{
		m_btnMgr.hide(m_config3LblGameLanguage, instant);
		m_btnMgr.hide(m_config3LblLanguage, instant);
		m_btnMgr.hide(m_config3BtnLanguageP, instant);
		m_btnMgr.hide(m_config3BtnLanguageM, instant);
		m_btnMgr.hide(m_config3LblGameVideo, instant);
		m_btnMgr.hide(m_config3LblVideo, instant);
		m_btnMgr.hide(m_config3BtnVideoP, instant);
		m_btnMgr.hide(m_config3BtnVideoM, instant);
	}
	else
	{
		m_btnMgr.hide(m_config3LblGCGameLanguage, instant);
		m_btnMgr.hide(m_config3LblGCLanguage, instant);
		m_btnMgr.hide(m_config3BtnGCLanguageP, instant);
		m_btnMgr.hide(m_config3BtnGCLanguageM, instant);
		m_btnMgr.hide(m_config3LblGCGameVideo, instant);
		m_btnMgr.hide(m_config3LblGCVideo, instant);
		m_btnMgr.hide(m_config3BtnGCVideoP, instant);
		m_btnMgr.hide(m_config3BtnGCVideoM, instant);
	}
	m_btnMgr.hide(m_config3LblGCGameLoader, instant);
	m_btnMgr.hide(m_config3LblGCLoader, instant);
	m_btnMgr.hide(m_config3BtnGCLoaderP, instant);
	m_btnMgr.hide(m_config3BtnGCLoaderM, instant);
	
	m_btnMgr.hide(m_config3LblChannelsType, instant);
	m_btnMgr.hide(m_config3LblChannelsTypeVal, instant);
	m_btnMgr.hide(m_config3BtnChannelsTypeP, instant);
	m_btnMgr.hide(m_config3BtnChannelsTypeM, instant);
	
	for(u8 i = 0; i < ARRAY_SIZE(m_config3LblUser); ++i)
		if(m_config3LblUser[i] != -1)
			m_btnMgr.hide(m_config3LblUser[i], instant);
}

void CMenu::_showConfig3(void)
{
	_showConfigCommon(m_config3Bg, g_curPage);

	if(m_current_view != COVERFLOW_GAMECUBE)
	{
		m_btnMgr.show(m_config3LblGameLanguage);
		m_btnMgr.show(m_config3LblLanguage);
		m_btnMgr.show(m_config3BtnLanguageP);
		m_btnMgr.show(m_config3BtnLanguageM);
		m_btnMgr.show(m_config3LblGameVideo);
		m_btnMgr.show(m_config3LblVideo);
		m_btnMgr.show(m_config3BtnVideoP);
		m_btnMgr.show(m_config3BtnVideoM);
	}
	else
	{
		m_btnMgr.show(m_config3LblGCGameLanguage);
		m_btnMgr.show(m_config3LblGCLanguage);
		m_btnMgr.show(m_config3BtnGCLanguageP);
		m_btnMgr.show(m_config3BtnGCLanguageM);
		m_btnMgr.show(m_config3LblGCGameVideo);
		m_btnMgr.show(m_config3LblGCVideo);
		m_btnMgr.show(m_config3BtnGCVideoP);
		m_btnMgr.show(m_config3BtnGCVideoM);
	}
	m_btnMgr.show(m_config3LblGCGameLoader);
	m_btnMgr.show(m_config3LblGCLoader);
	m_btnMgr.show(m_config3BtnGCLoaderP);
	m_btnMgr.show(m_config3BtnGCLoaderM);

	m_btnMgr.show(m_config3LblChannelsType);
	m_btnMgr.show(m_config3LblChannelsTypeVal);
	m_btnMgr.show(m_config3BtnChannelsTypeP);
	m_btnMgr.show(m_config3BtnChannelsTypeM);

	for(u8 i = 0; i < ARRAY_SIZE(m_config3LblUser); ++i)
		if(m_config3LblUser[i] != -1)
			m_btnMgr.show(m_config3LblUser[i]);

	int i;

	if(m_current_view != COVERFLOW_GAMECUBE)
	{
		i = min(max(0, m_cfg.getInt("GENERAL", "video_mode", 0)), (int)ARRAY_SIZE(CMenu::_GlobalVideoModes) - 1);
		m_btnMgr.setText(m_config3LblVideo, _t(CMenu::_GlobalVideoModes[i].id, CMenu::_GlobalVideoModes[i].text));

		i = min(max(0, m_cfg.getInt("GENERAL", "game_language", 0)), (int)ARRAY_SIZE(CMenu::_languages) - 1);
		m_btnMgr.setText(m_config3LblLanguage, _t(CMenu::_languages[i].id, CMenu::_languages[i].text));
	}
	else
	{
		i = min(max(0, m_cfg.getInt(GC_DOMAIN, "video_mode", 0)), (int)ARRAY_SIZE(CMenu::_GlobalGCvideoModes) - 1);
		m_btnMgr.setText(m_config3LblGCVideo, _t(CMenu::_GlobalGCvideoModes[i].id, CMenu::_GlobalGCvideoModes[i].text));
		
		i = min(max(0, m_cfg.getInt(GC_DOMAIN, "game_language", 0)), (int)ARRAY_SIZE(CMenu::_GlobalGClanguages) - 1);
		m_btnMgr.setText(m_config3LblGCLanguage, _t(CMenu::_GlobalGClanguages[i].id, CMenu::_GlobalGClanguages[i].text));
	}
	i = min(max(0, m_cfg.getInt(GC_DOMAIN, "default_loader", 2)), (int)ARRAY_SIZE(CMenu::_GlobalGCLoaders) - 1);
	m_btnMgr.setText(m_config3LblGCLoader, _t(CMenu::_GlobalGCLoaders[i].id, CMenu::_GlobalGCLoaders[i].text));

	i = m_cfg.getInt(CHANNEL_DOMAIN, "channels_type") - 1;
	m_btnMgr.setText(m_config3LblChannelsTypeVal, _t(CMenu::_ChannelsType[i].id, CMenu::_ChannelsType[i].text));
}

int CMenu::_config3(void)
{
	int change = CONFIG_PAGE_NO_CHANGE;

	_showConfig3();
	while(!m_exit)
	{
		change = _configCommon();
		if (change != CONFIG_PAGE_NO_CHANGE)
			break;
		if (BTN_A_PRESSED)
		{
			if (m_btnMgr.selected(m_config3BtnLanguageP) || m_btnMgr.selected(m_config3BtnLanguageM))
			{
				s8 direction = m_btnMgr.selected(m_config3BtnLanguageP) ? 1 : -1;
				m_cfg.setInt("GENERAL", "game_language", (int)loopNum((u32)m_cfg.getInt("GENERAL", "game_language", 0) + direction, ARRAY_SIZE(CMenu::_languages)));
				_showConfig3();
			}
			else if (m_btnMgr.selected(m_config3BtnVideoP) || m_btnMgr.selected(m_config3BtnVideoM))
			{
				s8 direction = m_btnMgr.selected(m_config3BtnVideoP) ? 1 : -1;
				m_cfg.setInt("GENERAL", "video_mode", (int)loopNum((u32)m_cfg.getInt("GENERAL", "video_mode", 0) + direction, ARRAY_SIZE(CMenu::_GlobalVideoModes)));
				_showConfig3();
			}
			else if (m_btnMgr.selected(m_config3BtnGCLanguageP) || m_btnMgr.selected(m_config3BtnGCLanguageM))
			{
				s8 direction = m_btnMgr.selected(m_config3BtnGCLanguageP) ? 1 : -1;
				m_cfg.setInt(GC_DOMAIN, "game_language", (int)loopNum((u32)m_cfg.getInt(GC_DOMAIN, "game_language", 0) + direction, ARRAY_SIZE(CMenu::_GlobalGClanguages)));
				_showConfig3();
			}
			else if (m_btnMgr.selected(m_config3BtnGCVideoP) || m_btnMgr.selected(m_config3BtnGCVideoM))
			{
				s8 direction = m_btnMgr.selected(m_config3BtnGCVideoP) ? 1 : -1;
				m_cfg.setInt(GC_DOMAIN, "video_mode", (int)loopNum((u32)m_cfg.getInt(GC_DOMAIN, "video_mode", 0) + direction, ARRAY_SIZE(CMenu::_GlobalGCvideoModes)));
				_showConfig3();
			}
			else if (m_btnMgr.selected(m_config3BtnGCLoaderP) || m_btnMgr.selected(m_config3BtnGCLoaderM))
			{
				s8 direction = m_btnMgr.selected(m_config3BtnGCLoaderP) ? 1 : -1;
				m_cfg.setInt(GC_DOMAIN, "default_loader", (int)loopNum((u32)m_cfg.getInt(GC_DOMAIN, "default_loader", 1) + direction, ARRAY_SIZE(CMenu::_GlobalGCLoaders)));
				_showConfig3();
			}
			else if (m_btnMgr.selected(m_config3BtnChannelsTypeP) || m_btnMgr.selected(m_config3BtnChannelsTypeM))
			{
				s8 direction = m_btnMgr.selected(m_config3BtnChannelsTypeP) ? 1 : -1;
				m_cfg.setInt(CHANNEL_DOMAIN, "channels_type", 1 + (int)loopNum((u32)m_cfg.getInt(CHANNEL_DOMAIN, "channels_type", 1) - 1 + direction, ARRAY_SIZE(CMenu::_ChannelsType)));
				_showConfig3();
				if(m_current_view & COVERFLOW_CHANNEL)
					m_refreshGameList = true;
			}
		}
	}
	_hideConfig3();
	return change;
}

void CMenu::_initConfig3Menu()
{
	_addUserLabels(m_config3LblUser, ARRAY_SIZE(m_config3LblUser), "CONFIG3");
	m_config3Bg = _texture("CONFIG3/BG", "texture", theme.bg, false);
	m_config3LblGameVideo = _addLabel("CONFIG3/VIDEO", theme.lblFont, L"", 20, 125, 290, 56, theme.lblFontColor, FTGX_JUSTIFY_LEFT | FTGX_ALIGN_MIDDLE);
	m_config3LblVideo = _addLabel("CONFIG3/VIDEO_BTN", theme.btnFont, L"", 468, 130, 104, 48, theme.btnFontColor, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE, theme.btnTexC);
	m_config3BtnVideoM = _addPicButton("CONFIG3/VIDEO_MINUS", theme.btnTexMinus, theme.btnTexMinusS, 420, 130, 48, 48);
	m_config3BtnVideoP = _addPicButton("CONFIG3/VIDEO_PLUS", theme.btnTexPlus, theme.btnTexPlusS, 572, 130, 48, 48);
	m_config3LblGameLanguage = _addLabel("CONFIG3/GAME_LANG", theme.lblFont, L"", 20, 185, 290, 56, theme.lblFontColor, FTGX_JUSTIFY_LEFT | FTGX_ALIGN_MIDDLE);
	m_config3LblLanguage = _addLabel("CONFIG3/GAME_LANG_BTN", theme.btnFont, L"", 468, 190, 104, 48, theme.btnFontColor, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE, theme.btnTexC);
	m_config3BtnLanguageM = _addPicButton("CONFIG3/GAME_LANG_MINUS", theme.btnTexMinus, theme.btnTexMinusS, 420, 190, 48, 48);
	m_config3BtnLanguageP = _addPicButton("CONFIG3/GAME_LANG_PLUS", theme.btnTexPlus, theme.btnTexPlusS, 572, 190, 48, 48);

	m_config3LblGCGameVideo = _addLabel("CONFIG3/DML_VIDEO", theme.lblFont, L"", 20, 125, 290, 56, theme.lblFontColor, FTGX_JUSTIFY_LEFT | FTGX_ALIGN_MIDDLE);
	m_config3LblGCVideo = _addLabel("CONFIG3/DML_VIDEO_BTN", theme.btnFont, L"", 468, 130, 104, 48, theme.btnFontColor, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE, theme.btnTexC);
	m_config3BtnGCVideoM = _addPicButton("CONFIG3/DML_VIDEO_MINUS", theme.btnTexMinus, theme.btnTexMinusS, 420, 130, 48, 48);
	m_config3BtnGCVideoP = _addPicButton("CONFIG3/DML_VIDEO_PLUS", theme.btnTexPlus, theme.btnTexPlusS, 572, 130, 48, 48);
	m_config3LblGCGameLanguage = _addLabel("CONFIG3/DML_LANG", theme.lblFont, L"", 20, 185, 290, 56, theme.lblFontColor, FTGX_JUSTIFY_LEFT | FTGX_ALIGN_MIDDLE);
	m_config3LblGCLanguage = _addLabel("CONFIG3/DML_LANG_BTN", theme.btnFont, L"", 468, 190, 104, 48, theme.btnFontColor, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE, theme.btnTexC);
	m_config3BtnGCLanguageM = _addPicButton("CONFIG3/DML_LANG_MINUS", theme.btnTexMinus, theme.btnTexMinusS, 420, 190, 48, 48);
	m_config3BtnGCLanguageP = _addPicButton("CONFIG3/DML_LANG_PLUS", theme.btnTexPlus, theme.btnTexPlusS, 572, 190, 48, 48);
	m_config3LblGCGameLoader = _addLabel("CONFIG3/GC_LOADER", theme.lblFont, L"", 20, 245, 290, 56, theme.lblFontColor, FTGX_JUSTIFY_LEFT | FTGX_ALIGN_MIDDLE);
	m_config3LblGCLoader = _addLabel("CONFIG3/GC_LOADER_BTN", theme.btnFont, L"", 468, 250, 104, 48, theme.btnFontColor, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE, theme.btnTexC);
	m_config3BtnGCLoaderM = _addPicButton("CONFIG3/GC_LOADER_MINUS", theme.btnTexMinus, theme.btnTexMinusS, 420, 250, 48, 48);
	m_config3BtnGCLoaderP = _addPicButton("CONFIG3/GC_LOADER_PLUS", theme.btnTexPlus, theme.btnTexPlusS, 572, 250, 48, 48);
	
	m_config3LblChannelsType = _addLabel("CONFIG3/CHANNELS_TYPE", theme.lblFont, L"", 20, 305, 290, 56, theme.lblFontColor, FTGX_JUSTIFY_LEFT | FTGX_ALIGN_MIDDLE);
	m_config3LblChannelsTypeVal = _addLabel("CONFIG3/CHANNELS_TYPE_BTN", theme.btnFont, L"", 468, 310, 104, 48, theme.btnFontColor, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE, theme.btnTexC);
	m_config3BtnChannelsTypeM = _addPicButton("CONFIG3/CHANNELS_TYPE_MINUS", theme.btnTexMinus, theme.btnTexMinusS, 420, 310, 48, 48);
	m_config3BtnChannelsTypeP = _addPicButton("CONFIG3/CHANNELS_TYPE_PLUS", theme.btnTexPlus, theme.btnTexPlusS, 572, 310, 48, 48);

	_setHideAnim(m_config3LblGameVideo, "CONFIG3/VIDEO", 50, 0, -2.f, 0.f);
	_setHideAnim(m_config3LblVideo, "CONFIG3/VIDEO_BTN", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnVideoM, "CONFIG3/VIDEO_MINUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnVideoP, "CONFIG3/VIDEO_PLUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3LblGameLanguage, "CONFIG3/GAME_LANG", 50, 0, -2.f, 0.f);
	_setHideAnim(m_config3LblLanguage, "CONFIG3/GAME_LANG_BTN", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnLanguageM, "CONFIG3/GAME_LANG_MINUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnLanguageP, "CONFIG3/GAME_LANG_PLUS", -50, 0, 1.f, 0.f);

	_setHideAnim(m_config3LblGCGameVideo, "CONFIG3/DML_VIDEO", 50, 0, -2.f, 0.f);
	_setHideAnim(m_config3LblGCVideo, "CONFIG3/DML_VIDEO_BTN", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnGCVideoM, "CONFIG3/DML_VIDEO_MINUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnGCVideoP, "CONFIG3/DML_VIDEO_PLUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3LblGCGameLanguage, "CONFIG3/DML_LANG", 50, 0, -2.f, 0.f);
	_setHideAnim(m_config3LblGCLanguage, "CONFIG3/DML_LANG_BTN", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnGCLanguageM, "CONFIG3/DML_LANG_MINUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnGCLanguageP, "CONFIG3/DML_LANG_PLUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3LblGCGameLoader, "CONFIG3/GC_LOADER", 50, 0, -2.f, 0.f);
	_setHideAnim(m_config3LblGCLoader, "CONFIG3/GC_LOADER_BTN", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnGCLoaderM, "CONFIG3/GC_LOADER_MINUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnGCLoaderP, "CONFIG3/GC_LOADER_PLUS", -50, 0, 1.f, 0.f);
	
	_setHideAnim(m_config3LblChannelsType, "CONFIG3/CHANNELS_TYPE", 50, 0, -2.f, 0.f);
	_setHideAnim(m_config3LblChannelsTypeVal, "CONFIG3/CHANNELS_TYPE_BTN", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnChannelsTypeM, "CONFIG3/CHANNELS_TYPE_MINUS", -50, 0, 1.f, 0.f);
	_setHideAnim(m_config3BtnChannelsTypeP, "CONFIG3/CHANNELS_TYPE_PLUS", -50, 0, 1.f, 0.f);
	_hideConfig3(true);
	_textConfig3();
}

void CMenu::_textConfig3(void)
{
	m_btnMgr.setText(m_config3LblGameVideo, _t("cfgb3", L"Default video mode"));
	m_btnMgr.setText(m_config3LblGameLanguage, _t("cfgb4", L"Default game language"));
	m_btnMgr.setText(m_config3LblGCGameVideo, _t("cfgb5", L"Default GC video mode"));
	m_btnMgr.setText(m_config3LblGCGameLanguage, _t("cfgb6", L"Default GC game language"));
	m_btnMgr.setText(m_config3LblGCGameLoader, _t("cfgb2", L"Default GC game loader"));
	m_btnMgr.setText(m_config3LblChannelsType, _t("cfgb7", L"Channels Type"));
}

