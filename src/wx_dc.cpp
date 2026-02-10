#include "wrapper.h"
#include <wx/dcbuffer.h>
#include <wx/dcmirror.h>
#include <wx/metafile.h>

extern "C"
{
    EXPORT void wxDC_Delete(wxDC* self)
    {
        delete self;
    }

    EXPORT void wxDC_FloodFill(wxDC* self, int x, int y, wxColour* col, int style)
    {
        self->FloodFill((wxCoord) x, (wxCoord) y, *col, (wxFloodFillStyle) style);
    }

    EXPORT int wxDC_GetPixel(wxDC* self, int x, int y, wxColour* col)
    {
        return self->GetPixel((wxCoord) x, (wxCoord) y, col);
    }

    EXPORT void wxDC_DrawLine(wxDC* self, int x1, int y1, int x2, int y2)
    {
        self->DrawLine((wxCoord) x1, (wxCoord) y1, (wxCoord) x2, (wxCoord) y2);
    }

    EXPORT void wxDC_CrossHair(wxDC* self, int x, int y)
    {
        self->CrossHair((wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_DrawArc(wxDC* self, int x1, int y1, int x2, int y2, int xc, int yc)
    {
        self->DrawArc((wxCoord) x1, (wxCoord) y1, (wxCoord) x2, (wxCoord) y2, (wxCoord) xc,
                      (wxCoord) yc);
    }

    EXPORT void wxDC_DrawCheckMark(wxDC* self, int x, int y, int width, int height)
    {
        self->DrawCheckMark((wxCoord) x, (wxCoord) y, (wxCoord) width, (wxCoord) height);
    }

    EXPORT void wxDC_DrawEllipticArc(wxDC* self, int x, int y, int w, int h, double sa, double ea)
    {
        self->DrawEllipticArc((wxCoord) x, (wxCoord) y, (wxCoord) w, (wxCoord) h, sa, ea);
    }

    EXPORT void wxDC_DrawPoint(wxDC* self, int x, int y)
    {
        self->DrawPoint((wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_DrawLines(wxDC* self, int count, void* x, void* y, int xoffset, int yoffset)
    {
        wxPoint* lst = (wxPoint*) malloc(count * sizeof(wxPoint));

        for (int i = 0; i < count; i++)
            lst[i] = wxPoint((int) ((intptr_t*) x)[i], (int) ((intptr_t*) y)[i]);

        self->DrawLines(count, lst, (wxCoord) xoffset, (wxCoord) yoffset);

        free(lst);
    }

    EXPORT void wxDC_DrawPolygon(wxDC* self, int count, void* x, void* y, int xoffset, int yoffset,
                                 int fillStyle)
    {
        wxPolygonFillMode style = (wxPolygonFillMode) fillStyle;
        wxPoint* lst = (wxPoint*) malloc(count * sizeof(wxPoint));

        for (int i = 0; i < count; i++)
            lst[i] = wxPoint(((intptr_t*) x)[i], ((intptr_t*) y)[i]);

        self->DrawPolygon(count, lst, (wxCoord) xoffset, (wxCoord) yoffset, style);

        free(lst);
    }

    EXPORT void wxDC_DrawRectangle(wxDC* self, int x, int y, int width, int height)
    {
        self->DrawRectangle((wxCoord) x, (wxCoord) y, (wxCoord) width, (wxCoord) height);
    }

    EXPORT void wxDC_DrawRoundedRectangle(wxDC* self, int x, int y, int width, int height,
                                          double radius)
    {
        self->DrawRoundedRectangle((wxCoord) x, (wxCoord) y, (wxCoord) width, (wxCoord) height,
                                   radius);
    }

    EXPORT void wxDC_DrawCircle(wxDC* self, int x, int y, int radius)
    {
        self->DrawCircle((wxCoord) x, (wxCoord) y, (wxCoord) radius);
    }

    EXPORT void wxDC_DrawEllipse(wxDC* self, int x, int y, int width, int height)
    {
        self->DrawEllipse((wxCoord) x, (wxCoord) y, (wxCoord) width, (wxCoord) height);
    }

    EXPORT void wxDC_DrawIcon(wxDC* self, wxIcon* icon, int x, int y)
    {
        self->DrawIcon(*icon, (wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_DrawBitmap(wxDC* self, wxBitmap* bmp, int x, int y, bool useMask)
    {
        self->DrawBitmap(*bmp, (wxCoord) x, (wxCoord) y, useMask);
    }

    EXPORT void wxDC_DrawText(wxDC* self, wxString* text, int x, int y)
    {
        self->DrawText(*text, (wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_DrawRotatedText(wxDC* self, wxString* text, int x, int y, double angle)
    {
        self->DrawRotatedText(*text, (wxCoord) x, (wxCoord) y, angle);
    }

    EXPORT bool wxDC_Blit(wxDC* self, int xdest, int ydest, int width, int height, wxDC* source,
                          int xsrc, int ysrc, int rop, bool useMask, int xsrcMask, int ysrcMask)
    {
        wxRasterOperationMode rasterOp = (wxRasterOperationMode) rop;
        return self->Blit((wxCoord) xdest, (wxCoord) ydest, (wxCoord) width, (wxCoord) height,
                          source, (wxCoord) xsrc, (wxCoord) ysrc, rasterOp, useMask,
                          (wxCoord) xsrcMask, (wxCoord) ysrcMask);
    }

    EXPORT void wxDC_Clear(wxDC* self)
    {
        self->Clear();
    }

    EXPORT void wxDC_ComputeScaleAndOrigin(wxDC* dc)
    {
        // Function removed in wxWidgets 2.9+
    }

    EXPORT bool wxDC_StartDoc(wxDC* self, wxString* msg)
    {
        return self->StartDoc(*msg);
    }

    EXPORT void wxDC_EndDoc(wxDC* self)
    {
        self->EndDoc();
    }

    EXPORT void wxDC_StartPage(wxDC* self)
    {
        self->StartPage();
    }

    EXPORT void wxDC_EndPage(wxDC* self)
    {
        self->EndPage();
    }

    EXPORT void wxDC_SetFont(wxDC* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxDC_SetPen(wxDC* self, wxPen* pen)
    {
        self->SetPen(*pen);
    }

    EXPORT void wxDC_SetBrush(wxDC* self, wxBrush* brush)
    {
        self->SetBrush(*brush);
    }

    EXPORT void wxDC_SetBackground(wxDC* self, wxBrush* brush)
    {
        self->SetBackground(*brush);
    }

    EXPORT void wxDC_SetBackgroundMode(wxDC* self, int mode)
    {
        self->SetBackgroundMode(mode);
    }

    EXPORT void wxDC_SetPalette(wxDC* self, wxPalette* palette)
    {
        self->SetPalette(*palette);
    }

    EXPORT void wxDC_SetClippingRegion(wxDC* self, int x, int y, int width, int height)
    {
        self->SetClippingRegion((wxCoord) x, (wxCoord) y, (wxCoord) width, (wxCoord) height);
    }

    EXPORT void wxDC_SetClippingRegionFromRegion(wxDC* self, wxRegion* region)
    {
        self->SetDeviceClippingRegion(*region);
    }

    EXPORT void wxDC_SetDeviceClippingRegion(wxDC* self, wxRegion* region)
    {
        self->SetDeviceClippingRegion(*region);
    }

    EXPORT void wxDC_DestroyClippingRegion(wxDC* self)
    {
        self->DestroyClippingRegion();
    }

    EXPORT void wxDC_GetClippingBox(wxDC* self, wxCoord* x, wxCoord* y, wxCoord* w, wxCoord* h)
    {
        self->GetClippingBox(x, y, w, h);
    }

    EXPORT wxCoord wxDC_GetCharHeight(wxDC* self)
    {
        return self->GetCharHeight();
    }

    EXPORT wxCoord wxDC_GetCharWidth(wxDC* self)
    {
        return self->GetCharWidth();
    }

    EXPORT void wxDC_GetTextExtent(wxDC* self, wxString* string, wxCoord* w, wxCoord* h,
                                   wxCoord* descent, wxCoord* externalLeading, wxFont* theFont)
    {
        self->GetTextExtent(*string, w, h, descent, externalLeading, theFont);
    }

    EXPORT void wxDC_GetMultiLineTextExtent(wxDC* self, wxString* string, wxCoord* w, wxCoord* h,
                                            wxCoord* heightLine, wxFont* theFont)
    {
        self->GetMultiLineTextExtent(*string, w, h, heightLine, theFont);
    }

    EXPORT wxSize* wxDC_GetSize(wxDC* self)
    {
        wxSize* s = new wxSize();
        *s = self->GetSize();
        return s;
    }

    EXPORT wxSize* wxDC_GetSizeMM(wxDC* self)
    {
        wxSize* s = new wxSize();
        *s = self->GetSizeMM();
        return s;
    }

    EXPORT wxCoord wxDC_DeviceToLogicalX(wxDC* self, wxCoord x)
    {
        return self->DeviceToLogicalX(x);
    }

    EXPORT wxCoord wxDC_DeviceToLogicalY(wxDC* self, wxCoord y)
    {
        return self->DeviceToLogicalY(y);
    }

    EXPORT wxCoord wxDC_DeviceToLogicalXRel(wxDC* self, wxCoord x)
    {
        return self->DeviceToLogicalXRel(x);
    }

    EXPORT wxCoord wxDC_DeviceToLogicalYRel(wxDC* self, int y)
    {
        return self->DeviceToLogicalYRel((wxCoord) y);
    }

    EXPORT wxCoord wxDC_LogicalToDeviceX(wxDC* self, int x)
    {
        return self->LogicalToDeviceX((wxCoord) x);
    }

    EXPORT wxCoord wxDC_LogicalToDeviceY(wxDC* self, int y)
    {
        return self->LogicalToDeviceY((wxCoord) y);
    }

    EXPORT wxCoord wxDC_LogicalToDeviceXRel(wxDC* self, int x)
    {
        return self->LogicalToDeviceXRel((wxCoord) x);
    }

    EXPORT wxCoord wxDC_LogicalToDeviceYRel(wxDC* self, int y)
    {
        return self->LogicalToDeviceYRel((wxCoord) y);
    }

    EXPORT bool wxDC_CanDrawBitmap(wxDC* self)
    {
        return self->CanDrawBitmap();
    }

    EXPORT bool wxDC_CanGetTextExtent(wxDC* self)
    {
        return self->CanGetTextExtent();
    }

    EXPORT int wxDC_GetDepth(wxDC* self)
    {
        return self->GetDepth();
    }

    EXPORT wxSize* wxDC_GetPPI(wxDC* self)
    {
        wxSize* s = new wxSize();
        *s = self->GetPPI();
        return s;
    }

    EXPORT bool wxDC_IsOk(wxDC* self)
    {
        return self->IsOk();
    }

    EXPORT int wxDC_GetBackgroundMode(wxDC* self)
    {
        return self->GetBackgroundMode();
    }

    EXPORT void wxDC_GetBackground(wxDC* self, wxBrush* ref)
    {
        *ref = self->GetBackground();
    }

    EXPORT void wxDC_GetBrush(wxDC* self, wxBrush* ref)
    {
        *ref = self->GetBrush();
    }

    EXPORT void wxDC_GetFont(wxDC* self, wxFont* ref)
    {
        *ref = self->GetFont();
    }

    EXPORT void wxDC_GetPen(wxDC* self, wxPen* ref)
    {
        *ref = self->GetPen();
    }

    EXPORT void wxDC_GetTextBackground(wxDC* self, wxColour* ref)
    {
        *ref = self->GetTextBackground();
    }

    EXPORT void wxDC_GetTextForeground(wxDC* self, wxColour* ref)
    {
        *ref = self->GetTextForeground();
    }

    EXPORT void wxDC_SetTextForeground(wxDC* self, wxColour* colour)
    {
        self->SetTextForeground(*colour);
    }

    EXPORT void wxDC_SetTextBackground(wxDC* self, wxColour* colour)
    {
        self->SetTextBackground(*colour);
    }

    EXPORT int wxDC_GetMapMode(wxDC* self)
    {
        return self->GetMapMode();
    }

    EXPORT void wxDC_SetMapMode(wxDC* self, int mode)
    {
        self->SetMapMode((wxMappingMode) mode);
    }

    EXPORT void wxDC_GetUserScale(wxDC* self, double* x, double* y)
    {
        self->GetUserScale(x, y);
    }

    EXPORT void wxDC_SetUserScale(wxDC* self, double x, double y)
    {
        self->SetUserScale(x, y);
    }

    EXPORT void wxDC_GetLogicalScale(wxDC* self, double* x, double* y)
    {
        self->GetLogicalScale(x, y);
    }

    EXPORT void wxDC_SetLogicalScale(wxDC* self, double x, double y)
    {
        self->SetLogicalScale(x, y);
    }

    EXPORT void wxDC_GetLogicalOrigin(wxDC* self, wxCoord* x, wxCoord* y)
    {
        self->GetLogicalOrigin(x, y);
    }

    EXPORT void wxDC_SetLogicalOrigin(wxDC* self, int x, int y)
    {
        self->SetLogicalOrigin((wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_GetDeviceOrigin(wxDC* self, wxCoord* x, wxCoord* y)
    {
        self->GetDeviceOrigin(x, y);
    }

    EXPORT void wxDC_SetDeviceOrigin(wxDC* self, int x, int y)
    {
        self->SetDeviceOrigin((wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_SetAxisOrientation(wxDC* self, bool xLeftRight, bool yBottomUp)
    {
        self->SetAxisOrientation(xLeftRight, yBottomUp);
    }

    EXPORT int wxDC_GetLogicalFunction(wxDC* self)
    {
        return self->GetLogicalFunction();
    }

    EXPORT void wxDC_SetLogicalFunction(wxDC* self, int function)
    {
        self->SetLogicalFunction((wxRasterOperationMode) function);
    }

    EXPORT void wxDC_CalcBoundingBox(wxDC* self, int x, int y)
    {
        self->CalcBoundingBox((wxCoord) x, (wxCoord) y);
    }

    EXPORT void wxDC_ResetBoundingBox(wxDC* self)
    {
        self->ResetBoundingBox();
    }

    EXPORT wxCoord wxDC_MinX(wxDC* self)
    {
        return self->MinX();
    }

    EXPORT wxCoord wxDC_MaxX(wxDC* self)
    {
        return self->MaxX();
    }

    EXPORT wxCoord wxDC_MinY(wxDC* self)
    {
        return self->MinY();
    }

    EXPORT wxCoord wxDC_MaxY(wxDC* self)
    {
        return self->MaxY();
    }

    EXPORT wxWindowDC* wxWindowDC_Create(wxWindow* win)
    {
        return new wxWindowDC(win);
    }

    EXPORT void wxWindowDC_Delete(wxWindowDC* self)
    {
        delete self;
    }

    EXPORT wxClientDC* wxClientDC_Create(wxWindow* win)
    {
        return new wxClientDC(win);
    }

    EXPORT void wxClientDC_Delete(wxClientDC* self)
    {
        delete self;
    }

    EXPORT wxPaintDC* wxPaintDC_Create(wxWindow* win)
    {
        return new wxPaintDC(win);
    }

    EXPORT void wxPaintDC_Delete(wxPaintDC* self)
    {
        delete self;
    }

    EXPORT wxMemoryDC* wxMemoryDC_Create()
    {
        return new wxMemoryDC();
    }

    EXPORT wxMemoryDC* wxMemoryDC_CreateCompatible(wxDC* dc)
    {
        return new wxMemoryDC(dc);
    }

    EXPORT wxMemoryDC* wxMemoryDC_CreateWithBitmap(wxBitmap* bitmap)
    {
        return new wxMemoryDC(*bitmap);
    }

    EXPORT void wxMemoryDC_Delete(wxMemoryDC* self)
    {
        delete self;
    }

    EXPORT void wxMemoryDC_SelectObject(wxMemoryDC* self, wxBitmap* bitmap)
    {
        self->SelectObject(*bitmap);
    }

    EXPORT wxMirrorDC* wxMirrorDC_Create(wxDC* dc, bool mirror)
    {
        return new wxMirrorDC(*dc, mirror);
    }

    EXPORT void wxMirrorDC_Delete(wxMirrorDC* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxScreenDC* wxScreenDC_Create()
    {
        return new wxScreenDC();
    }

    EXPORT void wxScreenDC_Delete(wxScreenDC* self)
    {
        delete self;
    }

    EXPORT bool wxScreenDC_StartDrawingOnTopOfWin(wxScreenDC* self, wxWindow* win)
    {
        return self->StartDrawingOnTop(win);
    }

    EXPORT bool wxScreenDC_StartDrawingOnTop(wxScreenDC* self, int l, int t, int w, int h)
    {
        wxRect rect(l, t, w, h);
        return self->StartDrawingOnTop(&rect);
    }

    EXPORT bool wxScreenDC_EndDrawingOnTop(wxScreenDC* self)
    {
        return self->EndDrawingOnTop();
    }

    EXPORT wxBufferedDC* wxBufferedDC_CreateByDCAndSize(wxDC* dc, int width, int hight, int style)
    {
        return new wxBufferedDC(dc, wxSize(width, hight), style);
    }

    EXPORT wxBufferedDC* wxBufferedDC_CreateByDCAndBitmap(wxDC* dc, wxBitmap* buffer, int style)
    {
        return new wxBufferedDC(dc, *buffer, style);
    }

    EXPORT void wxBufferedDC_Delete(wxBufferedDC* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxBufferedPaintDC* wxBufferedPaintDC_Create(wxWindow* window, int style)
    {
        return new wxBufferedPaintDC(window, style);
    }

    EXPORT wxBufferedPaintDC* wxBufferedPaintDC_CreateWithBitmap(wxWindow* window, wxBitmap* buffer,
                                                                 int style)
    {
        return new wxBufferedPaintDC(window, *buffer, style);
    }

    EXPORT void wxBufferedPaintDC_Delete(wxBufferedPaintDC* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxAutoBufferedPaintDC* wxAutoBufferedPaintDC_Create(wxWindow* window)
    {
        return new wxAutoBufferedPaintDC(window);
    }

    EXPORT void wxAutoBufferedPaintDC_Delete(wxAutoBufferedPaintDC* self)
    {
        if (self)
            delete self;
    }

    EXPORT void* wxMetafileDC_Create(wxString* filePath)
    {
#if defined(__WXGTK__)
        return nullptr;
#else
        wxString file;

        if (filePath)
            file = (char*) filePath;

        return (void*) new wxMetafileDC(file);
#endif
    }

    EXPORT void* wxMetafileDC_Close(void* self)
    {
#if defined(__WXGTK__)
        return nullptr;
#else
        return (void*) ((wxMetafileDC*) self)->Close();
#endif
    }

    EXPORT void wxMetafileDC_Delete(void* self)
    {
#if !defined(__WXGTK__)
        delete (wxMetafileDC*) self;
#endif
    }

    EXPORT void* wxMetafile_Create(wxString* filePath)
    {
#if defined(__WXGTK__)
        return nullptr;
#else
        wxString file;

        if (filePath)
            file = (char*) filePath;

        return (void*) new wxMetafile(file);
#endif
    }

    EXPORT bool wxMetafile_SetClipboard(void* self, int width, int height)
    {
#if defined(__WXGTK__)
        return false;
#else
        return ((wxMetafile*) self)->SetClipboard(width, height);
#endif
    }

    EXPORT bool wxMetafile_Play(void* self, wxDC* dc)
    {
#if defined(__WXGTK__)
        return false;
#else
        return ((wxMetafile*) self)->Play(dc);
#endif
    }

    EXPORT bool wxMetafile_IsOk(void* self)
    {
#if defined(__WXGTK__)
        return false;
#else
        return ((wxMetafile*) self)->IsOk();
#endif
    }

    EXPORT void wxMetafile_Delete(void* self)
    {
#if !defined(__WXGTK__)
        delete (wxMetafile*) self;
#endif
    }

    EXPORT void wxDC_DrawLabel(wxDC* self, wxString* str, int x, int y, int w, int h, int align,
                               int indexAccel)
    {
        wxRect rect(x, y, w, h);
        self->DrawLabel(*str, rect, align, indexAccel);
    }

    EXPORT wxRect* wxDC_DrawLabelBitmap(wxDC* self, wxString* str, wxBitmap* bmp, int x, int y,
                                        int w, int h, int align, int indexAccel)
    {
        wxRect rect(x, y, w, h);
        wxRect* r = new wxRect();
        self->DrawLabel(*str, *bmp, rect, align, indexAccel, r);
        return r;
    }

    EXPORT void wxDC_DrawPolyPolygon(wxDC* self, int numPolygons, int* count, void* x, void* y,
                                     int xoffset, int yoffset, int fillStyle)
    {
        int* tmp = count;
        int* cnt = new int[numPolygons];
        int i, j;
        int totalItems = 0;
        int item = 0;

        // Work out the size of wxPoint array required
        for (i = 0; i < numPolygons; i++)
        {
            cnt[i] = *tmp++;
            totalItems += cnt[i];
        }
        wxPoint* lst = new wxPoint[totalItems];

        for (i = 0; i < numPolygons; i++)
        {
            for (j = 0; j < cnt[i]; j++)
            {
                lst[item] = wxPoint(((intptr_t*) x)[item], ((intptr_t*) y)[item]);
                item++;
            }
        }

        self->DrawPolyPolygon(numPolygons, cnt, lst, (wxCoord) xoffset, (wxCoord) yoffset,
                              (wxPolygonFillMode) fillStyle);

        free(lst);
        delete cnt;
    }
}
