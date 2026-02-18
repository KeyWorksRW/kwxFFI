#include "wrapper.h"

#include <wx/dcgraph.h>
#include <wx/graphics.h>

extern "C"
{
    EXPORT wxGCDC* wxGcdc_Create(const wxWindowDC* dc)
    {
        return new wxGCDC(*dc);
    }

    EXPORT wxGCDC* wxGcdc_CreateFromMemory(const wxMemoryDC* dc)
    {
        return new wxGCDC(*dc);
    }

    EXPORT wxGCDC* wxGcdc_CreateFromPrinter(const wxPrinterDC* dc)
    {
        return new wxGCDC(*dc);
    }

    EXPORT wxGraphicsContext* wxGcdc_GetGraphicsContext(const wxGCDC* self)
    {
        return self->GetGraphicsContext();
    }

    EXPORT void wxGcdc_SetGraphicsContext(wxGCDC* self, wxGraphicsContext* gc)
    {
        self->SetGraphicsContext(gc);
    }

    EXPORT void wxGcdc_Delete(wxGCDC* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_Create(const wxWindowDC* dc)
    {
        return wxGraphicsContext::Create(*dc);
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromMemory(const wxMemoryDC* dc)
    {
        return wxGraphicsContext::Create(*dc);
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromPrinter(const wxPrinterDC* dc)
    {
        return wxGraphicsContext::Create(*dc);
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromWindow(wxWindow* window)
    {
        return wxGraphicsContext::Create(window);
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromNative(void* context)
    {
        return wxGraphicsContext::CreateFromNative(context);
    }

    EXPORT wxGraphicsContext* wxGraphicsContext_CreateFromNativeWindow(void* window)
    {
        return wxGraphicsContext::CreateFromNativeWindow(window);
    }

    EXPORT void wxGraphicsContext_Delete(wxGraphicsContext* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxGraphicsMatrix* wxGraphicsContext_CreateMatrix(wxGraphicsContext* self, double a,
                                                            double b, double c, double d, double tx,
                                                            double ty)
    {
        wxGraphicsMatrix* matrix = new wxGraphicsMatrix;
        *matrix = self->CreateMatrix(a, b, c, d, tx, ty);
        return matrix;
    }

    EXPORT wxGraphicsMatrix* wxGraphicsContext_CreateDefaultMatrix(wxGraphicsContext* self)
    {
        wxGraphicsMatrix* matrix = new wxGraphicsMatrix;
        *matrix = self->CreateMatrix(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        return matrix;
    }

    EXPORT wxGraphicsPath* wxGraphicsContext_CreatePath(wxGraphicsContext* self)
    {
        wxGraphicsPath* path = new wxGraphicsPath;
        *path = self->CreatePath();
        return path;
    }

    EXPORT void wxGraphicsContext_Clip(wxGraphicsContext* self, const wxRegion* region)
    {
        self->Clip(*region);
    }

    EXPORT void wxGraphicsContext_ClipByRectangle(wxGraphicsContext* self, wxDouble x, wxDouble y,
                                                  wxDouble width, wxDouble height)
    {
        self->Clip(x, y, width, height);
    }

    EXPORT void wxGraphicsContext_ResetClip(wxGraphicsContext* self)
    {
        self->ResetClip();
    }

    EXPORT void wxGraphicsContext_DrawBitmap(wxGraphicsContext* self, const wxBitmap* bmp,
                                             wxDouble x, wxDouble y, wxDouble width,
                                             wxDouble height)
    {
        self->DrawBitmap(*bmp, x, y, width, height);
    }

    EXPORT void wxGraphicsContext_DrawEllipse(wxGraphicsContext* self, wxDouble x, wxDouble y,
                                              wxDouble width, wxDouble height)
    {
        self->DrawEllipse(x, y, width, height);
    }

    EXPORT void wxGraphicsContext_DrawIcon(wxGraphicsContext* self, const wxIcon* icon, wxDouble x,
                                           wxDouble y, wxDouble width, wxDouble height)
    {
        self->DrawIcon(*icon, x, y, width, height);
    }

    EXPORT void wxGraphicsContext_DrawLines(wxGraphicsContext* self, size_t count, wxDouble* x,
                                            wxDouble* y, wxPolygonFillMode fillStyle)
    {
        auto points = std::make_unique<wxPoint2DDouble[]>(count);

        for (size_t i = 0; i < count; i++)
            points[i] = wxPoint2DDouble(x[i], y[i]);

        self->DrawLines(count, points.get(), fillStyle);
    }

    EXPORT void wxGraphicsContext_DrawPath(wxGraphicsContext* self, const wxGraphicsPath* path,
                                           wxPolygonFillMode fillStyle)
    {
        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->DrawPath(*path, pfm_fillStyle);
    }

    EXPORT void wxGraphicsContext_DrawRectangle(wxGraphicsContext* self, wxDouble x, wxDouble y,
                                                wxDouble width, wxDouble height)
    {
        self->DrawRectangle(x, y, width, height);
    }

    EXPORT void wxGraphicsContext_DrawRoundedRectangle(wxGraphicsContext* self, wxDouble x,
                                                       wxDouble y, wxDouble width, wxDouble height,
                                                       wxDouble radius)
    {
        self->DrawRoundedRectangle(x, y, width, height, radius);
    }

    EXPORT void wxGraphicsContext_DrawText(wxGraphicsContext* self, const wxString* str, wxDouble x,
                                           wxDouble y)
    {
        self->DrawText((str ? *str : wxString("")), x, y);
    }

    EXPORT void wxGraphicsContext_DrawTextWithAngle(wxGraphicsContext* self, const wxString* str,
                                                    wxDouble x, wxDouble y, wxDouble angle)
    {
        self->DrawText((str ? *str : wxString("")), x, y, angle);
    }

    EXPORT void wxGraphicsContext_FillPath(wxGraphicsContext* self, const wxGraphicsPath* path,
                                           wxPolygonFillMode fillStyle)
    {
        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->FillPath(*path, pfm_fillStyle);
    }

    EXPORT void wxGraphicsContext_StrokePath(wxGraphicsContext* self, const wxGraphicsPath* path)
    {
        self->StrokePath(*path);
    }

    EXPORT void* wxGraphicsContext_GetNativeContext(wxGraphicsContext* self)
    {
        return self->GetNativeContext();
    }

    EXPORT void wxGraphicsContext_GetPartialTextExtents(wxGraphicsContext* self,
                                                        const wxString* text, double* widths,
                                                        size_t count)
    {
        wxArrayDouble wd;
        self->GetPartialTextExtents(*text, wd);
        size_t n = wxMin(wd.GetCount(), count);
        for (size_t i = 0; i < n; ++i)
            widths[i] = wd[i];
    }

    EXPORT void wxGraphicsContext_GetTextExtent(wxGraphicsContext* self, const wxString* text,
                                                wxDouble* width, wxDouble* height,
                                                wxDouble* descent, wxDouble* externalLeading)
    {
        self->GetTextExtent(*text, width, height, descent, externalLeading);
    }

    EXPORT void wxGraphicsContext_Rotate(wxGraphicsContext* self, wxDouble angle)
    {
        self->Rotate(angle);
    }

    EXPORT void wxGraphicsContext_Scale(wxGraphicsContext* self, wxDouble xScale, wxDouble yScale)
    {
        self->Scale(xScale, yScale);
    }

    EXPORT void wxGraphicsContext_Translate(wxGraphicsContext* self, wxDouble dx, wxDouble dy)
    {
        self->Translate(dx, dy);
    }

    EXPORT void wxGraphicsContext_SetTransform(wxGraphicsContext* self,
                                               const wxGraphicsMatrix* matrix)
    {
        self->SetTransform(*matrix);
    }

    EXPORT void wxGraphicsContext_ConcatTransform(wxGraphicsContext* self,
                                                  const wxGraphicsMatrix* matrix)
    {
        self->ConcatTransform(*matrix);
    }

    EXPORT void wxGraphicsContext_SetBrush(wxGraphicsContext* self, const wxBrush* brush)
    {
        self->SetBrush(*brush);
    }

    EXPORT void wxGraphicsContext_SetGraphicsBrush(wxGraphicsContext* self,
                                                   const wxGraphicsBrush* brush)
    {
        self->SetBrush(*brush);
    }

    EXPORT void wxGraphicsContext_SetFont(wxGraphicsContext* self, const wxFont* font,
                                          const wxColour* colour)
    {
        self->SetFont(*font, *colour);
    }

    EXPORT void wxGraphicsContext_SetGraphicsFont(wxGraphicsContext* self,
                                                  const wxGraphicsFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxGraphicsContext_SetPen(wxGraphicsContext* self, const wxPen* pen)
    {
        self->SetPen(*pen);
    }

    EXPORT void wxGraphicsContext_SetGraphicsPen(wxGraphicsContext* self, const wxGraphicsPen* pen)
    {
        self->SetPen(*pen);
    }

    EXPORT void wxGraphicsContext_StrokeLine(wxGraphicsContext* self, wxDouble x1, wxDouble y1,
                                             wxDouble x2, wxDouble y2)
    {
        self->StrokeLine(x1, y1, x2, y2);
    }

    EXPORT void wxGraphicsContext_StrokeLines(wxGraphicsContext* self, size_t count, wxDouble* x,
                                              wxDouble* y, wxPolygonFillMode fillStyle)
    {
        auto points = std::make_unique<wxPoint2DDouble[]>(count);

        for (size_t i = 0; i < count; i++)
            points[i] = wxPoint2DDouble(x[i], y[i]);

        self->StrokeLines(count, points.get());
    }

    EXPORT void wxGraphicsContext_StrokeLinesStartAndEnd(wxGraphicsContext* self, size_t count,
                                                         const wxPoint2DDouble* beginPoints,
                                                         const wxPoint2DDouble* endPoints)
    {
        self->StrokeLines(count, beginPoints, endPoints);
    }

    EXPORT void wxGraphicsContext_PushState(wxGraphicsContext* self)
    {
        self->PushState();
    }

    EXPORT void wxGraphicsContext_PopState(wxGraphicsContext* self)
    {
        self->PopState();
    }

    EXPORT wxGraphicsObject* wxGraphicsObject_Create()
    {
        return new wxGraphicsObject;
    }

    EXPORT void wxGraphicsObject_Delete(wxGraphicsObject* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxGraphicsRenderer* wxGraphicsObject_GetRenderer(wxGraphicsObject* self)
    {
        return self->GetRenderer();
    }

    EXPORT bool wxGraphicsObject_IsNull(wxGraphicsObject* self)
    {
        return self->IsNull();
    }

    EXPORT wxGraphicsBrush* wxGraphicsBrush_Create()
    {
        return new wxGraphicsBrush;
    }

    EXPORT void wxGraphicsBrush_Delete(wxGraphicsBrush* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxGraphicsFont* wxGraphicsFont_Create()
    {
        return new wxGraphicsFont;
    }

    EXPORT void wxGraphicsFont_Delete(wxGraphicsFont* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxGraphicsMatrix* wxGraphicsMatrix_Create()
    {
        return new wxGraphicsMatrix;
    }

    EXPORT void wxGraphicsMatrix_Delete(wxGraphicsMatrix* self)
    {
        if (self)
            delete self;
    }

    EXPORT void wxGraphicsMatrix_Concat(wxGraphicsMatrix* self, const wxGraphicsMatrix* matrix)
    {
        self->Concat(matrix);
    }

    EXPORT void wxGraphicsMatrix_Get(wxGraphicsMatrix* self, wxDouble* a, wxDouble* b, wxDouble* c,
                                     wxDouble* d, wxDouble* tx, wxDouble* ty)
    {
        self->Get(a, b, c, d, tx, ty);
    }

    EXPORT void* wxGraphicsMatrix_GetNativeMatrix(wxGraphicsMatrix* self)
    {
        return self->GetNativeMatrix();
    }

    EXPORT void wxGraphicsMatrix_Invert(wxGraphicsMatrix* self)
    {
        self->Invert();
    }

    EXPORT bool wxGraphicsMatrix_IsEqual(wxGraphicsMatrix* self, const wxGraphicsMatrix* t)
    {
        return self->IsEqual(*t);
    }

    EXPORT bool wxGraphicsMatrix_IsIdentity(wxGraphicsMatrix* self)
    {
        return self->IsIdentity();
    }

    EXPORT void wxGraphicsMatrix_Rotate(wxGraphicsMatrix* self, wxDouble angle)
    {
        self->Rotate(angle);
    }

    EXPORT void wxGraphicsMatrix_Scale(wxGraphicsMatrix* self, wxDouble xScale, wxDouble yScale)
    {
        self->Scale(xScale, yScale);
    }

    EXPORT void wxGraphicsMatrix_Translate(wxGraphicsMatrix* self, wxDouble dx, wxDouble dy)
    {
        self->Translate(dx, dy);
    }

    EXPORT void wxGraphicsMatrix_Set(wxGraphicsMatrix* self, wxDouble a, wxDouble b, wxDouble c,
                                     wxDouble d, wxDouble tx, wxDouble ty)
    {
        self->Set(a, b, c, d, tx, ty);
    }

    EXPORT void wxGraphicsMatrix_TransformPoint(wxGraphicsMatrix* self, wxDouble* x, wxDouble* y)
    {
        self->TransformPoint(x, y);
    }

    EXPORT void wxGraphicsMatrix_TransformDistance(wxGraphicsMatrix* self, wxDouble* dx,
                                                   wxDouble* dy)
    {
        self->TransformDistance(dx, dy);
    }

    EXPORT void wxGraphicsPath_Delete(wxGraphicsPath* self)
    {
        if (self)
            delete self;
    }

    EXPORT void wxGraphicsPath_MoveToPoint(wxGraphicsPath* self, wxDouble x, wxDouble y)
    {
        self->MoveToPoint(x, y);
    }

    EXPORT void wxGraphicsPath_AddArc(wxGraphicsPath* self, wxDouble x, wxDouble y, wxDouble r,
                                      wxDouble startAngle, wxDouble endAngle, bool clockwise)
    {
        self->AddArc(x, y, r, startAngle, endAngle, clockwise);
    }

    EXPORT void wxGraphicsPath_AddArcToPoint(wxGraphicsPath* self, wxDouble x1, wxDouble y1,
                                             wxDouble x2, wxDouble y2, wxDouble r)
    {
        self->AddArcToPoint(x1, y1, x2, y2, r);
    }

    EXPORT void wxGraphicsPath_AddCircle(wxGraphicsPath* self, wxDouble x, wxDouble y, wxDouble r)
    {
        self->AddCircle(x, y, r);
    }

    EXPORT void wxGraphicsPath_AddCurveToPoint(wxGraphicsPath* self, wxDouble cx1, wxDouble cy1,
                                               wxDouble cx2, wxDouble cy2, wxDouble x, wxDouble y)
    {
        self->AddCurveToPoint(cx1, cy1, cx2, cy2, x, y);
    }

    EXPORT void wxGraphicsPath_AddEllipse(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                          wxDouble width, wxDouble height)
    {
        self->AddEllipse(x, y, width, height);
    }

    EXPORT void wxGraphicsPath_AddLineToPoint(wxGraphicsPath* self, wxDouble x, wxDouble y)
    {
        self->AddLineToPoint(x, y);
    }

    EXPORT void wxGraphicsPath_AddPath(wxGraphicsPath* self, const wxGraphicsPath* path)
    {
        self->AddPath(*path);
    }

    EXPORT void wxGraphicsPath_AddQuadCurveToPoint(wxGraphicsPath* self, wxDouble cx, wxDouble cy,
                                                   wxDouble x, wxDouble y)
    {
        self->AddQuadCurveToPoint(cx, cy, x, y);
    }

    EXPORT void wxGraphicsPath_AddRectangle(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                            wxDouble width, wxDouble height)
    {
        self->AddRectangle(x, y, width, height);
    }

    EXPORT void wxGraphicsPath_AddRoundedRectangle(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                                   wxDouble width, wxDouble height, wxDouble radius)
    {
        self->AddRoundedRectangle(x, y, width, height, radius);
    }

    EXPORT void wxGraphicsPath_CloseSubpath(wxGraphicsPath* self)
    {
        self->CloseSubpath();
    }

    EXPORT void wxGraphicsPath_Contains(wxGraphicsPath* self, wxDouble x, wxDouble y,
                                        wxPolygonFillMode fillStyle)
    {
        wxPolygonFillMode pfm_fillStyle = (wxPolygonFillMode) fillStyle;

        self->Contains(x, y, pfm_fillStyle);
    }

    EXPORT void wxGraphicsPath_GetBox(wxGraphicsPath* self, wxDouble* x, wxDouble* y,
                                      wxDouble* width, wxDouble* height)
    {
        self->GetBox(x, y, width, height);
    }

    EXPORT void wxGraphicsPath_GetCurrentPoint(wxGraphicsPath* self, wxDouble* x, wxDouble* y)
    {
        self->GetCurrentPoint(x, y);
    }

    EXPORT void wxGraphicsPath_Transform(wxGraphicsPath* self, const wxGraphicsMatrix* matrix)
    {
        self->Transform(*matrix);
    }

    EXPORT void* wxGraphicsPath_GetNativePath(wxGraphicsPath* self)
    {
        return self->GetNativePath();
    }

    EXPORT void wxGraphicsPath_UnGetNativePath(wxGraphicsPath* self, void* nativePath)
    {
        self->UnGetNativePath(nativePath);
    }

    EXPORT wxGraphicsPen* wxGraphicsPen_Create()
    {
        return new wxGraphicsPen;
    }

    EXPORT void wxGraphicsPen_Delete(wxGraphicsPen* self)
    {
        if (self)
            delete self;
    }

    // We can't create wxGraphicsRenderer by this function.
    // Because wxGraphicsRenderer is a abstract class.
    //
    // EXPORT wxGraphicsRenderer*wxGraphicsRenderer_Create( )
    // {
    //   return new wxGraphicsRenderer;
    // }

    EXPORT void wxGraphicsRenderer_Delete(wxGraphicsRenderer* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxGraphicsRenderer* wxGraphicsRenderer_GetDefaultRenderer(wxGraphicsRenderer* self)
    {
        return self->GetDefaultRenderer();
    }

    EXPORT wxGraphicsContext* wxGraphicsRenderer_CreateContext(wxGraphicsRenderer* self,
                                                               const wxWindowDC* dc)
    {
        return self->CreateContext(*dc);
    }

    EXPORT wxGraphicsContext* wxGraphicsRenderer_CreateContextFromWindow(wxGraphicsRenderer* self,
                                                                         wxWindow* window)
    {
        return self->CreateContext(window);
    }

    EXPORT wxGraphicsContext*
        wxGraphicsRenderer_CreateContextFromNativeContext(wxGraphicsRenderer* self, void* context)
    {
        return self->CreateContextFromNativeContext(context);
    }

    EXPORT wxGraphicsContext*
        wxGraphicsRenderer_CreateContextFromNativeWindow(wxGraphicsRenderer* self, void* window)
    {
        return self->CreateContextFromNativeWindow(window);
    }

    EXPORT wxGraphicsPath* wxGraphicsRenderer_CreatePath(wxGraphicsRenderer* self)
    {
        wxGraphicsPath* path = new wxGraphicsPath;
        *path = self->CreatePath();
        return path;
    }
}
