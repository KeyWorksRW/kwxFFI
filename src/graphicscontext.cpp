#include "wrapper.h"

/*-----------------------------------------------------------------------------
  We want to include the function signatures always -- even on
  systems that don't support wxGraphicsContext. This means that every function body is
  surrounded by #ifdef wxUSE_GRAPHICS_CONTEXT directives :-(
-----------------------------------------------------------------------------*/

#if defined(wxUSE_GRAPHICS_CONTEXT) && (wxUSE_GRAPHICS_CONTEXT == 0)
    #undef wxUSE_GRAPHICS_CONTEXT
#endif

#ifdef wxUSE_GRAPHICS_CONTEXT
    #include <wx/dcgraph.h>
    #include <wx/graphics.h>
#endif

#ifndef wxUSE_GRAPHICS_CONTEXT
    #define wxPoint2DDouble    void
    #define wxGraphicsBrush    void
    #define wxGraphicsContext  void
    #define wxGraphicsFont     void
    #define wxGraphicsMatrix   void
    #define wxGraphicsObject   void
    #define wxGraphicsPath     void
    #define wxGraphicsPen      void
    #define wxGraphicsRenderer void
    #define wxGCDC             void
#endif

extern "C"
{
    /*-----------------------------------------------------------------------------
      GCDC
    -----------------------------------------------------------------------------*/

    EXPORT wxGCDC* wxGcdc_Create(const wxWindowDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGCDC(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGCDC* wxGcdc_CreateFromMemory(const wxMemoryDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGCDC(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGCDC* wxGcdc_CreateFromPrinter(const wxPrinterDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGCDC(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGcdc_GetGraphicsContext(const wxGCDC* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->GetGraphicsContext();
#else
        return nullptr;
#endif
    }

    EXPORT void wxGcdc_SetGraphicsContext(wxGCDC* self, wxGraphicsContext* gc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetGraphicsContext(gc);
#else
        return;
#endif
    }

    EXPORT void wxGcdc_Delete(wxGCDC* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsContext
    -----------------------------------------------------------------------------*/
    EXPORT wxGraphicsContext* wxGraphicsContext_Create(const wxWindowDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return wxGraphicsContext::Create(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromMemory(const wxMemoryDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return wxGraphicsContext::Create(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromPrinter(const wxPrinterDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return wxGraphicsContext::Create(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromWindow(wxWindow* window)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return wxGraphicsContext::Create(window);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromNative(void* context)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return wxGraphicsContext::CreateFromNative(context);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromNativeWindow(void* window)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return wxGraphicsContext::CreateFromNativeWindow(window);
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsContext_Delete(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    EXPORT wxGraphicsMatrix* wxGraphicsContext_CreateMatrix(wxGraphicsContext* self, double a,
                                                            double b, double c, double d, double tx,
                                                            double ty)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxGraphicsMatrix* matrix = new wxGraphicsMatrix;
        *matrix = self->CreateMatrix(a, b, c, d, tx, ty);
        return matrix;
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsMatrix* wxGraphicsContext_CreateDefaultMatrix(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxGraphicsMatrix* matrix = new wxGraphicsMatrix;
        *matrix = self->CreateMatrix(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        return matrix;
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsPath* wxGraphicsContext_CreatePath(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxGraphicsPath* path = new wxGraphicsPath;
        *path = self->CreatePath();
        return path;
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsContext_Clip(wxGraphicsContext* self, const wxRegion* region)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Clip(*region);
#endif
    }

    EXPORT void wxGraphicsContext_ClipByRectangle(wxGraphicsContext* self, wxDouble x, wxDouble y,
                                                  wxDouble w, wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Clip(x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsContext_ResetClip(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->ResetClip();
#endif
    }

    EXPORT void wxGraphicsContext_DrawBitmap(wxGraphicsContext* self, const wxBitmap* bmp,
                                             wxDouble x, wxDouble y, wxDouble w, wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawBitmap(*bmp, x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsContext_DrawEllipse(wxGraphicsContext* self, wxDouble x, wxDouble y,
                                              wxDouble w, wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawEllipse(x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsContext_DrawIcon(wxGraphicsContext* self, const wxIcon* icon, wxDouble x,
                                           wxDouble y, wxDouble w, wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawIcon(*icon, x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsContext_DrawLines(wxGraphicsContext* self, size_t n, wxDouble* x,
                                            wxDouble* y, wxPolygonFillMode fillStyle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxPoint2DDouble* points = (wxPoint2DDouble*) malloc(n * sizeof(wxPoint2DDouble));

        for (size_t i = 0; i < n; i++)
            points[i] = wxPoint2DDouble(x[i], y[i]);

        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->DrawLines(n, points, pfm_fillStyle);

        free(points);
#endif
    }

    EXPORT void wxGraphicsContext_DrawPath(wxGraphicsContext* self, const wxGraphicsPath* path,
                                           wxPolygonFillMode fillStyle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->DrawPath(*path, pfm_fillStyle);
#endif
    }

    EXPORT void wxGraphicsContext_DrawRectangle(wxGraphicsContext* self, wxDouble x, wxDouble y,
                                                wxDouble w, wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawRectangle(x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsContext_DrawRoundedRectangle(wxGraphicsContext* self, wxDouble x,
                                                       wxDouble y, wxDouble w, wxDouble h,
                                                       wxDouble radius)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawRoundedRectangle(x, y, w, h, radius);
#endif
    }

    EXPORT void wxGraphicsContext_DrawText(wxGraphicsContext* self, const wxString* str, wxDouble x,
                                           wxDouble y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawText((str ? *str : wxString("")), x, y);
#endif
    }

    EXPORT void wxGraphicsContext_DrawTextWithAngle(wxGraphicsContext* self, const wxString* str,
                                                    wxDouble x, wxDouble y, wxDouble angle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->DrawText((str ? *str : wxString("")), x, y, angle);
#endif
    }

    EXPORT void wxGraphicsContext_FillPath(wxGraphicsContext* self, const wxGraphicsPath* path,
                                           wxPolygonFillMode fillStyle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->FillPath(*path, pfm_fillStyle);
#endif
    }

    EXPORT void wxGraphicsContext_StrokePath(wxGraphicsContext* self, const wxGraphicsPath* path)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->StrokePath(*path);
#endif
    }

    EXPORT void* wxGraphicsContext_GetNativeContext(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->GetNativeContext();
#else
        return nullptr;
#endif
    }

    /*
    TODO: Implement wrapper function of wxGraphicsContext::GetPartialTextExtents.
    */

    EXPORT void wxGraphicsContext_GetTextExtent(wxGraphicsContext* self, const wxString* text,
                                                wxDouble* width, wxDouble* height,
                                                wxDouble* descent, wxDouble* externalLeading)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->GetTextExtent(*text, width, height, descent, externalLeading);
#endif
    }

    EXPORT void wxGraphicsContext_Rotate(wxGraphicsContext* self, wxDouble angle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Rotate(angle);
#endif
    }

    EXPORT void wxGraphicsContext_Scale(wxGraphicsContext* self, wxDouble xScale, wxDouble yScale)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Scale(xScale, yScale);
#endif
    }

    EXPORT void wxGraphicsContext_Translate(wxGraphicsContext* self, wxDouble dx, wxDouble dy)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Translate(dx, dy);
#endif
    }

    EXPORT void wxGraphicsContext_SetTransform(wxGraphicsContext* self,
                                               const wxGraphicsMatrix* matrix)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetTransform(*matrix);
#endif
    }

    EXPORT void wxGraphicsContext_ConcatTransform(wxGraphicsContext* self,
                                                  const wxGraphicsMatrix* matrix)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->ConcatTransform(*matrix);
#endif
    }

    EXPORT void wxGraphicsContext_SetBrush(wxGraphicsContext* self, const wxBrush* brush)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetBrush(*brush);
#endif
    }

    EXPORT void wxGraphicsContext_SetGraphicsBrush(wxGraphicsContext* self,
                                                   const wxGraphicsBrush* brush)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetBrush(*brush);
#endif
    }

    EXPORT void wxGraphicsContext_SetFont(wxGraphicsContext* self, const wxFont* font,
                                          const wxColour* colour)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetFont(*font, *colour);
#endif
    }

    EXPORT void wxGraphicsContext_SetGraphicsFont(wxGraphicsContext* self,
                                                  const wxGraphicsFont* font)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetFont(*font);
#endif
    }

    EXPORT void wxGraphicsContext_SetPen(wxGraphicsContext* self, const wxPen* pen)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetPen(*pen);
#endif
    }

    EXPORT void wxGraphicsContext_SetGraphicsPen(wxGraphicsContext* self, const wxGraphicsPen* pen)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->SetPen(*pen);
#endif
    }

    EXPORT void wxGraphicsContext_StrokeLine(wxGraphicsContext* self, wxDouble x1, wxDouble y1,
                                             wxDouble x2, wxDouble y2)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->StrokeLine(x1, y1, x2, y2);
#endif
    }

    EXPORT void wxGraphicsContext_StrokeLines(wxGraphicsContext* self, size_t n, wxDouble* x,
                                              wxDouble* y, wxPolygonFillMode fillStyle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxPoint2DDouble* points = (wxPoint2DDouble*) malloc(n * sizeof(wxPoint2DDouble));

        for (size_t i = 0; i < n; i++)
            points[i] = wxPoint2DDouble(x[i], y[i]);

        self->StrokeLines(n, points);

        free(points);
#endif
    }

    EXPORT void wxGraphicsContext_StrokeLinesStartAndEnd(wxGraphicsContext* self, size_t n,
                                                         const wxPoint2DDouble* beginPoints,
                                                         const wxPoint2DDouble* endPoints)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->StrokeLines(n, beginPoints, endPoints);
#endif
    }

    EXPORT void wxGraphicsContext_PushState(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->PushState();
#endif
    }

    EXPORT void wxGraphicsContext_PopState(wxGraphicsContext* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->PopState();
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsObject
    -----------------------------------------------------------------------------*/
    EXPORT wxGraphicsObject* wxGraphicsObject_Create()
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGraphicsObject;
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsObject_Delete(wxGraphicsObject* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    EXPORT wxGraphicsRenderer* wxGraphicsObject_GetRenderer(wxGraphicsObject* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->GetRenderer();
#else
        return nullptr;
#endif
    }

    EXPORT bool wxGraphicsObject_IsNull(wxGraphicsObject* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->IsNull();
#else
        return false;
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsBrush
    -----------------------------------------------------------------------------*/
    EXPORT wxGraphicsBrush* wxGraphicsBrush_Create()
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGraphicsBrush;
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsBrush_Delete(wxGraphicsBrush* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsFont
    -----------------------------------------------------------------------------*/
    EXPORT wxGraphicsFont* wxGraphicsFont_Create()
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGraphicsFont;
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsFont_Delete(wxGraphicsFont* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsMatrix
    -----------------------------------------------------------------------------*/
    EXPORT wxGraphicsMatrix* wxGraphicsMatrix_Create()
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGraphicsMatrix;
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsMatrix_Delete(wxGraphicsMatrix* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    EXPORT void wxGraphicsMatrix_Concat(wxGraphicsMatrix* self, const wxGraphicsMatrix* matrix)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Concat(matrix);
#endif
    }

    EXPORT void wxGraphicsMatrix_Get(wxGraphicsMatrix* self, wxDouble* a, wxDouble* b, wxDouble* c,
                                     wxDouble* d, wxDouble* tx, wxDouble* ty)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Get(a, b, c, d, tx, ty);
#endif
    }

    EXPORT void* wxGraphicsMatrix_GetNativeMatrix(wxGraphicsMatrix* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->GetNativeMatrix();
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsMatrix_Invert(wxGraphicsMatrix* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Invert();
#endif
    }

    EXPORT bool wxGraphicsMatrix_IsEqual(wxGraphicsMatrix* self, const wxGraphicsMatrix* t)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->IsEqual(*t);
#else
        return false;
#endif
    }

    EXPORT bool wxGraphicsMatrix_IsIdentity(wxGraphicsMatrix* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->IsIdentity();
#else
        return false;
#endif
    }

    EXPORT void wxGraphicsMatrix_Rotate(wxGraphicsMatrix* self, wxDouble angle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Rotate(angle);
#endif
    }

    EXPORT void wxGraphicsMatrix_Scale(wxGraphicsMatrix* self, wxDouble xScale, wxDouble yScale)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Scale(xScale, yScale);
#endif
    }

    EXPORT void wxGraphicsMatrix_Translate(wxGraphicsMatrix* self, wxDouble dx, wxDouble dy)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Translate(dx, dy);
#endif
    }

    EXPORT void wxGraphicsMatrix_Set(wxGraphicsMatrix* self, wxDouble a, wxDouble b, wxDouble c,
                                     wxDouble d, wxDouble tx, wxDouble ty)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Set(a, b, c, d, tx, ty);
#endif
    }

    EXPORT void wxGraphicsMatrix_TransformPoint(wxGraphicsMatrix* self, wxDouble* x, wxDouble* y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->TransformPoint(x, y);
#endif
    }

    EXPORT void wxGraphicsMatrix_TransformDistance(wxGraphicsMatrix* self, wxDouble* dx,
                                                   wxDouble* dy)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->TransformDistance(dx, dy);
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsPath
    -----------------------------------------------------------------------------*/
    EXPORT void wxGraphicsPath_Delete(wxGraphicsPath* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    EXPORT void wxGraphicsPath_MoveToPoint(wxGraphicsPath* self, wxDouble x, wxDouble y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->MoveToPoint(x, y);
#endif
    }

    EXPORT void wxGraphicsPath_AddArc(wxGraphicsPath* self, wxDouble x, wxDouble y, wxDouble r,
                                      wxDouble startAngle, wxDouble endAngle, bool clockwise)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddArc(x, y, r, startAngle, endAngle, clockwise);
#endif
    }

    EXPORT void wxGraphicsPath_AddArcToPoint(wxGraphicsPath* self, wxDouble x1, wxDouble y1,
                                             wxDouble x2, wxDouble y2, wxDouble r)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddArcToPoint(x1, y1, x2, y2, r);
#endif
    }

    EXPORT void wxGraphicsPath_AddCircle(wxGraphicsPath* self, wxDouble x, wxDouble y, wxDouble r)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddCircle(x, y, r);
#endif
    }

    EXPORT void wxGraphicsPath_AddCurveToPoint(wxGraphicsPath* self, wxDouble cx1, wxDouble cy1,
                                               wxDouble cx2, wxDouble cy2, wxDouble x, wxDouble y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddCurveToPoint(cx1, cy1, cx2, cy2, x, y);
#endif
    }

    EXPORT void wxGraphicsPath_AddEllipse(wxGraphicsPath* self, wxDouble x, wxDouble y, wxDouble w,
                                          wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddEllipse(x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsPath_AddLineToPoint(wxGraphicsPath* self, wxDouble x, wxDouble y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddLineToPoint(x, y);
#endif
    }

    EXPORT void wxGraphicsPath_AddPath(wxGraphicsPath* self, const wxGraphicsPath* path)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddPath(*path);
#endif
    }

    EXPORT void wxGraphicsPath_AddQuadCurveToPoint(wxGraphicsPath* self, wxDouble cx, wxDouble cy,
                                                   wxDouble x, wxDouble y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddQuadCurveToPoint(cx, cy, x, y);
#endif
    }

    EXPORT void wxGraphicsPath_AddRectangle(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                            wxDouble w, wxDouble h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddRectangle(x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsPath_AddRoundedRectangle(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                                   wxDouble w, wxDouble h, wxDouble radius)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->AddRoundedRectangle(x, y, w, h, radius);
#endif
    }

    EXPORT void wxGraphicsPath_CloseSubpath(wxGraphicsPath* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->CloseSubpath();
#endif
    }

    EXPORT void wxGraphicsPath_Contains(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                        wxPolygonFillMode fillStyle)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->Contains(x, y, pfm_fillStyle);
#endif
    }

    EXPORT void wxGraphicsPath_GetBox(wxGraphicsPath* self, wxDouble* x, wxDouble* y, wxDouble* w,
                                      wxDouble* h)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->GetBox(x, y, w, h);
#endif
    }

    EXPORT void wxGraphicsPath_GetCurrentPoint(wxGraphicsPath* self, wxDouble* x, wxDouble* y)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->GetCurrentPoint(x, y);
#endif
    }

    EXPORT void wxGraphicsPath_Transform(wxGraphicsPath* self, const wxGraphicsMatrix* matrix)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->Transform(*matrix);
#endif
    }

    EXPORT void* wxGraphicsPath_GetNativePath(wxGraphicsPath* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->GetNativePath();
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsPath_UnGetNativePath(wxGraphicsPath* self, void* p)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        self->UnGetNativePath(p);
#endif
    }

    /*-----------------------------------------------------------------------------
      GraphicsPen
    -----------------------------------------------------------------------------*/
    EXPORT wxGraphicsPen* wxGraphicsPen_Create()
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return new wxGraphicsPen;
#else
        return nullptr;
#endif
    }

    EXPORT void wxGraphicsPen_Delete(wxGraphicsPen* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    /* We can't create wxGraphicsRenderer by this function.
       Because wxGraphicsRenderer is a abstract class.

    EXPORT wxGraphicsRenderer*wxGraphicsRenderer_Create( )
    {
    #ifdef wxUSE_GRAPHICS_CONTEXT
      return new wxGraphicsRenderer;
    #else
      return nullptr;
    #endif
    }
    */

    EXPORT void wxGraphicsRenderer_Delete(wxGraphicsRenderer* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        if (self)
            delete self;
#endif
    }

    EXPORT wxGraphicsRenderer* wxGraphicsRenderer_GetDefaultRenderer(wxGraphicsRenderer* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->GetDefaultRenderer();
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsRenderer_CreateContext(wxGraphicsRenderer* self,
                                                               const wxWindowDC* dc)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->CreateContext(*dc);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext* wxGraphicsRenderer_CreateContextFromWindow(wxGraphicsRenderer* self,
                                                                         wxWindow* window)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->CreateContext(window);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext*
        wxGraphicsRenderer_CreateContextFromNativeContext(wxGraphicsRenderer* self, void* context)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->CreateContextFromNativeContext(context);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsContext*
        wxGraphicsRenderer_CreateContextFromNativeWindow(wxGraphicsRenderer* self, void* window)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        return self->CreateContextFromNativeWindow(window);
#else
        return nullptr;
#endif
    }

    EXPORT wxGraphicsPath* wxGraphicsRenderer_CreatePath(wxGraphicsRenderer* self)
    {
#ifdef wxUSE_GRAPHICS_CONTEXT
        wxGraphicsPath* path = new wxGraphicsPath;
        *path = self->CreatePath();
        return path;
#else
        return nullptr;
#endif
    }
}
