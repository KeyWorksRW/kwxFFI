#pragma once

/* Phase 9C: method fill for sizer, DC, drawing, image, bitmap, font and menu classes.
 *
 * These blocks extend the class definitions in kwx_classes.h.  kwxgen merges
 * repeated TClassDef/TClassDefExtend blocks by class name, so the declarations
 * below are appended to the existing wxSizer/wxDC/wxImage/... method lists.
 */

/* ------------------------------------------------------------------------- */
/* wxSizer                                                                   */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxSizer, wxObject) TBool
    wxSizer_RemoveSizer(TSelf(wxSizer) pObject, TClass(wxSizer) sizer);
TBool wxSizer_Remove(TSelf(wxSizer) pObject, int index);
void wxSizer_DeleteWindows(TSelf(wxSizer) pObject);
TClass(wxSize) wxSizer_ComputeFittingClientSize(TSelf(wxSizer) pObject, TClass(wxWindow) window);
TClass(wxSize) wxSizer_ComputeFittingWindowSize(TSelf(wxSizer) pObject, TClass(wxWindow) window);
TClass(wxSize) wxSizer_FitWithSize(TSelf(wxSizer) pObject, TClass(wxWindow) window);
int wxSizer_GetItemCount(TSelf(wxSizer) pObject);
TBool wxSizer_IsEmpty(TSelf(wxSizer) pObject);
TClass(wxSizerItem) wxSizer_GetItemById(TSelf(wxSizer) pObject, int id, TBool recursive);
void wxSizer_ShowItems(TSelf(wxSizer) pObject, TBool show);
TBool wxSizer_AreAnyItemsShown(TSelf(wxSizer) pObject);
TBool wxSizer_InformFirstDirection(TSelf(wxSizer) pObject, int direction, int size,
                                   int availableOtherDir);
void wxSizer_SetContainingWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window);

/* ------------------------------------------------------------------------- */
/* wxBoxSizer                                                                */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxBoxSizer, wxSizer) TBool wxBoxSizer_IsVertical(TSelf(wxBoxSizer) pObject);
void wxBoxSizer_SetOrientation(TSelf(wxBoxSizer) pObject, int orient);

/* ------------------------------------------------------------------------- */
/* wxGridSizer                                                               */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxGridSizer,
                wxSizer) int wxGridSizer_GetEffectiveColsCount(TSelf(wxGridSizer) pObject);
int wxGridSizer_GetEffectiveRowsCount(TSelf(wxGridSizer) pObject);

/* ------------------------------------------------------------------------- */
/* wxFlexGridSizer                                                           */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxFlexGridSizer, wxGridSizer) TBool
    wxFlexGridSizer_IsRowGrowable(TSelf(wxFlexGridSizer) pObject, size_t idx);
TBool wxFlexGridSizer_IsColGrowable(TSelf(wxFlexGridSizer) pObject, size_t idx);
void wxFlexGridSizer_SetFlexibleDirection(TSelf(wxFlexGridSizer) pObject, int direction);
int wxFlexGridSizer_GetFlexibleDirection(TSelf(wxFlexGridSizer) pObject);
void wxFlexGridSizer_SetNonFlexibleGrowMode(TSelf(wxFlexGridSizer) pObject, int mode);
int wxFlexGridSizer_GetNonFlexibleGrowMode(TSelf(wxFlexGridSizer) pObject);
int wxFlexGridSizer_GetRowHeights(TSelf(wxFlexGridSizer) pObject, void* heights);
int wxFlexGridSizer_GetColWidths(TSelf(wxFlexGridSizer) pObject, void* widths);

/* ------------------------------------------------------------------------- */
/* wxGridBagSizer                                                            */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxGridBagSizer, wxGridSizer) TClass(wxSize)
    wxGridBagSizer_GetCellSize(TSelf(wxGridBagSizer) pObject, int row, int col);
TClass(wxSizerItem) wxGridBagSizer_FindItem(TSelf(wxGridBagSizer) pObject, TClass(wxWindow) window);
TClass(wxSizerItem)
    wxGridBagSizer_FindItemSizer(TSelf(wxGridBagSizer) pObject, TClass(wxSizer) sizer);
TClass(wxSizerItem) wxGridBagSizer_FindItemAtPoint(TSelf(wxGridBagSizer) pObject, TPoint(x, y));
TClass(wxSizerItem) wxGridBagSizer_FindItemWithData(TSelf(wxGridBagSizer) pObject, void* userData);

/* ------------------------------------------------------------------------- */
/* wxDC                                                                      */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDC, wxObject) TClass(wxWindow) wxDC_GetWindow(TSelf(wxDC) pObject);
int wxDC_GetResolution(TSelf(wxDC) pObject);
double wxDC_GetContentScaleFactor(TSelf(wxDC) pObject);
int wxDC_FromDIP(TSelf(wxDC) pObject, int value);
int wxDC_ToDIP(TSelf(wxDC) pObject, int value);
TClass(wxSize) wxDC_FromDIPSize(TSelf(wxDC) pObject, TSize(width, height));
TClass(wxSize) wxDC_ToDIPSize(TSelf(wxDC) pObject, TSize(width, height));
void wxDC_SetLayoutDirection(TSelf(wxDC) pObject, int direction);
int wxDC_GetLayoutDirection(TSelf(wxDC) pObject);
TClass(wxSize) wxDC_GetTextExtentSize(TSelf(wxDC) pObject, TClass(wxString) string);
TClass(wxSize) wxDC_GetMultiLineTextExtentSize(TSelf(wxDC) pObject, TClass(wxString) string);
TBool wxDC_GetPartialTextExtents(TSelf(wxDC) pObject, TClass(wxString) text, int count,
                                 int* widths);
TClass(wxPoint) wxDC_DeviceToLogical(TSelf(wxDC) pObject, TPoint(x, y));
TClass(wxPoint) wxDC_LogicalToDevice(TSelf(wxDC) pObject, TPoint(x, y));
TClass(wxSize) wxDC_DeviceToLogicalRel(TSelf(wxDC) pObject, TSize(width, height));
TClass(wxSize) wxDC_LogicalToDeviceRel(TSelf(wxDC) pObject, TSize(width, height));
TClass(wxPoint) wxDC_GetLogicalOriginPoint(TSelf(wxDC) pObject);
TClass(wxPoint) wxDC_GetDeviceOriginPoint(TSelf(wxDC) pObject);
void wxDC_CopyAttributes(TSelf(wxDC) pObject, TClass(wxDC) dc);
void* wxDC_GetHandle(TSelf(wxDC) pObject);
void wxDC_DisableAutomaticBoundingBoxUpdates(TSelf(wxDC) pObject);
TBool wxDC_AreAutomaticBoundingBoxUpdatesEnabled(TSelf(wxDC) pObject);
void wxDC_SetClippingRegionPoint(TSelf(wxDC) pObject, TPoint(x, y), TSize(width, height));
TBool wxDC_GetClippingRect(TSelf(wxDC) pObject, TRectOutVoid(x, y, width, height));
TBool wxDC_FloodFillEx(TSelf(wxDC) pObject, TPoint(x, y), TClass(wxColour) col, int style);
void wxDC_GradientFillConcentric(TSelf(wxDC) pObject, TRect(x, y, width, height),
                                 TClass(wxColour) initialColour, TClass(wxColour) destColour);
void wxDC_GradientFillConcentricCenter(TSelf(wxDC) pObject, TRect(x, y, width, height),
                                       TClass(wxColour) initialColour, TClass(wxColour) destColour,
                                       TPoint(cx, cy));
void wxDC_GradientFillLinear(TSelf(wxDC) pObject, TRect(x, y, width, height),
                             TClass(wxColour) initialColour, TClass(wxColour) destColour,
                             int direction);
TBool wxDC_StretchBlit(TSelf(wxDC) pObject, TRect(dstX, dstY, dstWidth, dstHeight),
                       TClass(wxDC) source, TRect(srcX, srcY, srcWidth, srcHeight), int rop,
                       TBool useMask, TPoint(maskX, maskY));
TClass(wxBitmap) wxDC_GetAsBitmap(TSelf(wxDC) pObject, TRect(x, y, width, height), TBool useRect);
void wxDC_DrawSpline(TSelf(wxDC) pObject, TPoint(x1, y1), TPoint(x2, y2), TPoint(x3, y3));
void wxDC_DrawSplinePoints(TSelf(wxDC) pObject, int count, void* x, void* y);
TClass(wxGraphicsContext) wxDC_GetGraphicsContext(TSelf(wxDC) pObject);
void wxDC_SetGraphicsContext(TSelf(wxDC) pObject, TClass(wxGraphicsContext) ctx);

/* ------------------------------------------------------------------------- */
/* wxImage                                                                   */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxImage, wxObject) TBool
    wxImage_CreateFromXPMData(TSelf(wxImage) pObject, void* data);
void wxImage_Clear(TSelf(wxImage) pObject, int value);
TClass(wxImage)
    wxImage_Size(TSelf(wxImage) pObject, TSize(width, height), TPoint(x, y), int r, int g, int b);
TClass(wxImage) wxImage_ResampleNearest(TSelf(wxImage) pObject, TSize(width, height));
TClass(wxImage) wxImage_ResampleBox(TSelf(wxImage) pObject, TSize(width, height));
TClass(wxImage) wxImage_ResampleBilinear(TSelf(wxImage) pObject, TSize(width, height));
TClass(wxImage) wxImage_ResampleBicubic(TSelf(wxImage) pObject, TSize(width, height));
TClass(wxImage) wxImage_Blur(TSelf(wxImage) pObject, int radius);
TClass(wxImage) wxImage_BlurHorizontal(TSelf(wxImage) pObject, int radius);
TClass(wxImage) wxImage_BlurVertical(TSelf(wxImage) pObject, int radius);
TClass(wxImage) wxImage_ShrinkBy(TSelf(wxImage) pObject, int xFactor, int yFactor);
void wxImage_Resize(TSelf(wxImage) pObject, TSize(width, height), TPoint(x, y), int r, int g,
                    int b);
TClass(wxImage) wxImage_Rotate180(TSelf(wxImage) pObject);
TClass(wxImage) wxImage_ConvertToGreyscale(TSelf(wxImage) pObject);
TClass(wxImage) wxImage_ConvertToGreyscaleEx(TSelf(wxImage) pObject, double weightR, double weightG,
                                             double weightB);
TClass(wxImage) wxImage_ConvertToMono(TSelf(wxImage) pObject, TColorRGB(r, g, b));
TClass(wxImage) wxImage_ConvertToDisabled(TSelf(wxImage) pObject, TChar brightness);
TClass(wxImage) wxImage_ChangeLightness(TSelf(wxImage) pObject, int alpha);
void wxImage_SetRGBRect(TSelf(wxImage) pObject, TRect(x, y, width, height), TColorRGB(r, g, b));
void wxImage_SetAlpha(TSelf(wxImage) pObject, TPoint(x, y), TChar alpha);
TChar wxImage_GetAlphaPixel(TSelf(wxImage) pObject, TPoint(x, y));
TBool wxImage_FindFirstUnusedColour(TSelf(wxImage) pObject, TChar* r, TChar* g, TChar* b,
                                    TChar startR, TChar startG, TChar startB);
TBool wxImage_SetMaskFromImage(TSelf(wxImage) pObject, TClass(wxImage) mask, TColorRGB(mr, mg, mb));
TBool wxImage_ConvertAlphaToMask(TSelf(wxImage) pObject, TChar threshold);
TBool wxImage_ConvertAlphaToMaskColour(TSelf(wxImage) pObject, TColorRGB(mr, mg, mb),
                                       TChar threshold);
TBool wxImage_ConvertColourToAlpha(TSelf(wxImage) pObject, TColorRGB(r, g, b));
void wxImage_SetDefaultLoadFlags(int flags);
int wxImage_GetDefaultLoadFlags();
void wxImage_SetLoadFlags(TSelf(wxImage) pObject, int flags);
int wxImage_GetLoadFlags(TSelf(wxImage) pObject);
int wxImage_GetImageCount(TClass(wxString) name, int type);
TBool wxImage_SaveFileMime(TSelf(wxImage) pObject, TClass(wxString) name,
                           TClass(wxString) mimetype);
TBool wxImage_LoadFileMime(TSelf(wxImage) pObject, TClass(wxString) name, TClass(wxString) mimetype,
                           int index);
TBool wxImage_LoadStreamMime(TSelf(wxImage) pObject, TClass(wxInputStream) stream,
                             TClass(wxString) mimetype, int index);
TBool wxImage_SaveStreamMime(TSelf(wxImage) pObject, TClass(wxOutputStream) stream,
                             TClass(wxString) mimetype);
TClass(wxSize) wxImage_GetSize(TSelf(wxImage) pObject);
void wxImage_SetDataRGBA(TSelf(wxImage) pObject, void* data);
void* wxImage_GetAlphaData(TSelf(wxImage) pObject);
TBool wxImage_HasAlpha(TSelf(wxImage) pObject);
void wxImage_SetAlphaData(TSelf(wxImage) pObject, void* alpha, TBool staticData);
void wxImage_InitAlpha(TSelf(wxImage) pObject);
void wxImage_ClearAlpha(TSelf(wxImage) pObject);
TBool wxImage_IsTransparent(TSelf(wxImage) pObject, TPoint(x, y), TChar threshold);
TBool wxImage_GetOrFindMaskColour(TSelf(wxImage) pObject, TChar* r, TChar* g, TChar* b);
TBool wxImage_HasPalette(TSelf(wxImage) pObject);
TClass(wxPalette) wxImage_GetPalette(TSelf(wxImage) pObject);
void wxImage_SetPalette(TSelf(wxImage) pObject, TClass(wxPalette) palette);
void wxImage_RotateHue(TSelf(wxImage) pObject, double angle);
void wxImage_ChangeSaturation(TSelf(wxImage) pObject, double factor);
void wxImage_ChangeBrightness(TSelf(wxImage) pObject, double factor);
void wxImage_ChangeHSV(TSelf(wxImage) pObject, double angleH, double factorS, double factorV);
void wxImage_AddHandler(TClass(wxImageHandler) handler);
void wxImage_InsertHandler(TClass(wxImageHandler) handler);
TBool wxImage_RemoveHandler(TClass(wxString) name);
TClass(wxImageHandler) wxImage_FindHandlerByName(TClass(wxString) name);
TClass(wxImageHandler) wxImage_FindHandlerByExtension(TClass(wxString) extension, int imageType);
TClass(wxImageHandler) wxImage_FindHandlerByType(int imageType);
TClass(wxImageHandler) wxImage_FindHandlerMime(TClass(wxString) mimetype);
TClass(wxString) wxImage_GetImageExtWildcard();
void wxImage_CleanUpHandlers();
void wxImage_InitStandardHandlers();

/* ------------------------------------------------------------------------- */
/* wxBitmap                                                                  */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxBitmap, wxGDIObject) TBool
    wxBitmap_Init(TSelf(wxBitmap) pObject, TSize(width, height), int depth);
TClass(wxSize) wxBitmap_GetSize(TSelf(wxBitmap) pObject);
void wxBitmap_SetScaleFactor(TSelf(wxBitmap) pObject, double scale);
double wxBitmap_GetScaleFactor(TSelf(wxBitmap) pObject);
TClass(wxSize) wxBitmap_GetDIPSize(TSelf(wxBitmap) pObject);
TClass(wxSize) wxBitmap_GetLogicalSize(TSelf(wxBitmap) pObject);
double wxBitmap_GetLogicalWidth(TSelf(wxBitmap) pObject);
double wxBitmap_GetLogicalHeight(TSelf(wxBitmap) pObject);
TBool wxBitmap_CreateScaled(TSelf(wxBitmap) pObject, TSize(width, height), int depth, double scale);
TClass(wxImage) wxBitmap_ConvertToImage(TSelf(wxBitmap) pObject);
TClass(wxBitmap) wxBitmap_ConvertToDisabled(TSelf(wxBitmap) pObject, TChar brightness);
TClass(wxPalette) wxBitmap_GetPalette(TSelf(wxBitmap) pObject);
void wxBitmap_SetPalette(TSelf(wxBitmap) pObject, TClass(wxPalette) palette);
TBool wxBitmap_HasAlpha(TSelf(wxBitmap) pObject);
TBool wxBitmap_UseAlpha(TSelf(wxBitmap) pObject, TBool use);
void wxBitmap_ResetAlpha(TSelf(wxBitmap) pObject);
TBool wxBitmap_CopyFromIcon(TSelf(wxBitmap) pObject, TClass(wxIcon) icon);
TClass(wxBitmap) wxBitmap_NewFromPNGData(void* data, size_t size);

/* ------------------------------------------------------------------------- */
/* wxFont                                                                    */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxFont, wxGDIObject) double wxFont_GetFractionalPointSize(TSelf(wxFont) pObject);
TClass(wxSize) wxFont_GetPixelSize(TSelf(wxFont) pObject);
TBool wxFont_IsUsingSizeInPixels(TSelf(wxFont) pObject);
int wxFont_GetNumericWeight(TSelf(wxFont) pObject);
TBool wxFont_GetStrikethrough(TSelf(wxFont) pObject);
TClass(wxString) wxFont_GetNativeFontInfoDesc(TSelf(wxFont) pObject);
TClass(wxString) wxFont_GetNativeFontInfoUserDesc(TSelf(wxFont) pObject);
TBool wxFont_IsFixedWidth(TSelf(wxFont) pObject);
void wxFont_SetFractionalPointSize(TSelf(wxFont) pObject, double pointSize);
void wxFont_SetPixelSize(TSelf(wxFont) pObject, TSize(width, height));
void wxFont_SetNumericWeight(TSelf(wxFont) pObject, int weight);
void wxFont_SetStrikethrough(TSelf(wxFont) pObject, TBool strikethrough);
TBool wxFont_SetNativeFontInfo(TSelf(wxFont) pObject, TClass(wxString) info);
TBool wxFont_SetNativeFontInfoUserDesc(TSelf(wxFont) pObject, TClass(wxString) info);
void wxFont_SetSymbolicSize(TSelf(wxFont) pObject, int size);
void wxFont_SetSymbolicSizeRelativeTo(TSelf(wxFont) pObject, int size, int base);
int wxFont_AdjustToSymbolicSize(int size, int base);
int wxFont_ConvertFromLegacyWeightIfNecessary(int weight);
int wxFont_GetNumericWeightOf(int weight);
void wxFont_MakeBold(TSelf(wxFont) pObject);
void wxFont_MakeItalic(TSelf(wxFont) pObject);
void wxFont_MakeUnderlined(TSelf(wxFont) pObject);
void wxFont_MakeStrikethrough(TSelf(wxFont) pObject);
void wxFont_MakeLarger(TSelf(wxFont) pObject);
void wxFont_MakeSmaller(TSelf(wxFont) pObject);
void wxFont_Scale(TSelf(wxFont) pObject, float factor);
TClass(wxFont) wxFont_Bold(TSelf(wxFont) pObject);
TClass(wxFont) wxFont_Italic(TSelf(wxFont) pObject);
TClass(wxFont) wxFont_Underlined(TSelf(wxFont) pObject);
TClass(wxFont) wxFont_Strikethrough(TSelf(wxFont) pObject);
TClass(wxFont) wxFont_Larger(TSelf(wxFont) pObject);
TClass(wxFont) wxFont_Smaller(TSelf(wxFont) pObject);
TClass(wxFont) wxFont_Scaled(TSelf(wxFont) pObject, float factor);
TClass(wxFont) wxFont_GetBaseFont(TSelf(wxFont) pObject);
TBool wxFont_AddPrivateFont(TClass(wxString) filename);
TBool wxFont_IsEqual(TSelf(wxFont) pObject, TClass(wxFont) font);

/* ------------------------------------------------------------------------- */
/* wxMenu                                                                    */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxMenu, wxEvtHandler) TClass(wxMenuItem)
    wxMenu_AppendSubMenu(TSelf(wxMenu) pObject, TClass(wxMenu) submenu, TClass(wxString) text,
                         TClass(wxString) help);
TClass(wxMenuItem) wxMenu_RemoveItem(TSelf(wxMenu) pObject, int id);
TClass(wxString) wxMenu_GetLabel(TSelf(wxMenu) pObject, int id);
TClass(wxWindow) wxMenu_GetWindow(TSelf(wxMenu) pObject);
void wxMenu_Detach(TSelf(wxMenu) pObject);
void wxMenu_LockAccels(TBool locked);

/* ------------------------------------------------------------------------- */
/* wxMenuBar                                                                 */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxMenuBar, wxEvtHandler) TBool wxMenuBar_IsAttached(TSelf(wxMenuBar) pObject);
void wxMenuBar_Attach(TSelf(wxMenuBar) pObject, TClass(wxFrame) frame);
void wxMenuBar_Detach(TSelf(wxMenuBar) pObject);

/* ------------------------------------------------------------------------- */
/* wxAcceleratorEntry                                                        */
/* ------------------------------------------------------------------------- */

TClassDef(wxAcceleratorEntry) TClass(wxAcceleratorEntry)
    wxAcceleratorEntry_CreateFromString(TClass(wxString) str);
void wxAcceleratorEntry_SetMenuItem(TSelf(wxAcceleratorEntry) pObject, TClass(wxMenuItem) item);
TClass(wxMenuItem) wxAcceleratorEntry_GetMenuItem(TSelf(wxAcceleratorEntry) pObject);
TBool wxAcceleratorEntry_IsOk(TSelf(wxAcceleratorEntry) pObject);
TBool wxAcceleratorEntry_MatchesEvent(TSelf(wxAcceleratorEntry) pObject, TClass(wxKeyEvent) event);
TClass(wxString) wxAcceleratorEntry_ToString(TSelf(wxAcceleratorEntry) pObject);
TClass(wxString) wxAcceleratorEntry_ToRawString(TSelf(wxAcceleratorEntry) pObject);
TBool wxAcceleratorEntry_FromString(TSelf(wxAcceleratorEntry) pObject, TClass(wxString) str);

/* ------------------------------------------------------------------------- */
/* wxAcceleratorTable                                                        */
/* ------------------------------------------------------------------------- */

TClassDef(wxAcceleratorTable) TClass(wxAcceleratorTable)
    wxAcceleratorTable_CreateFromResource(TClass(wxString) resource);
TBool wxAcceleratorTable_IsOk(TSelf(wxAcceleratorTable) pObject);
TClass(wxAcceleratorEntry)
    wxAcceleratorTable_GetEntry(TSelf(wxAcceleratorTable) pObject, TClass(wxKeyEvent) event);
