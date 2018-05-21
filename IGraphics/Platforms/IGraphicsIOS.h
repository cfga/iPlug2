#pragma once

#include "IGraphicsNanoVG.h"
#include "IPlugGraphicsDelegate.h"

/** IGraphics platform class for IOS
*   @ingroup PlatformClasses */
class IGraphicsIOS : public IGraphicsNanoVG
{
public:
  IGraphicsIOS(IDelegate& dlg, int w, int h, int fps);
  virtual ~IGraphicsIOS();
  
  void SetBundleID(const char* bundleID) { mBundleID.Set(bundleID); }
  void CreateMetalLayer();

  void* OpenWindow(void* pWindow) override;
  void CloseWindow() override;
  bool WindowIsOpen() override;
  void Resize(int w, int h, float scale) override;

  int ShowMessageBox(const char* str, const char* caption, int type) override;
  void ForceEndUserEdit() override;

  const char* GetPlatformAPIStr() override;

  void UpdateTooltips() override {};

  void PromptForFile(WDL_String& fileName, WDL_String& path, EFileAction action, const char* ext) override;
  void PromptForDirectory(WDL_String& dir) override;
  bool PromptForColor(IColor& color, const char* str) override;
  
  IPopupMenu* CreatePopupMenu(IPopupMenu& menu, const IRECT& bounds, IControl* pCaller) override;
  void CreateTextEntry(IControl& control, const IText& text, const IRECT& bounds, const char* str) override;
  
  bool OpenURL(const char* url, const char* msgWindowTitle, const char* confirmMsg, const char* errMsgOnFailure) override;
  
  void* GetWindow() override;
  
  const char* GetBundleID()  { return mBundleID.Get(); }
  static int GetUserOSVersion();
  
  bool GetTextFromClipboard(WDL_String& str) override;

  void* mLayer = nullptr;

protected:
  bool OSFindResource(const char* name, const char* type, WDL_String& result) override;
  bool GetResourcePathFromBundle(const char* fileName, const char* searchExt, WDL_String& fullPath);
  bool GetResourcePathFromUsersMusicFolder(const char* fileName, const char* searchExt, WDL_String& fullPath);

private:
  void* mView = nullptr;
  WDL_String mBundleID;
};