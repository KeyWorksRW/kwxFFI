#include "wrapper.h"

extern "C"
{
    EXPORT void* wxSizerItem_Create(int width, int height, int option, int flag, int border,
                                    void* userData)
    {
        return (void*) new wxSizerItem(width, height, option, flag, border,
                                       new kwxDataObject(userData));
    }

    EXPORT void* wxSizerItem_CreateInWindow(wxWindow* window, int option, int flag, int border,
                                            void* userData)
    {
        return (void*) new wxSizerItem(window, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void* wxSizerItem_CreateInSizer(wxSizer* sizer, int option, int flag, int border,
                                           void* userData)
    {
        return (void*) new wxSizerItem(sizer, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT wxSize* wxSizerItem_GetSize(wxSizerItem* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetSize();
        return text;
    }

    EXPORT wxSize* wxSizerItem_CalcMin(wxSizerItem* self)
    {
        wxSize* text = new wxSize();
        *text = self->CalcMin();
        return text;
    }

    EXPORT void wxSizerItem_SetDimension(wxSizerItem* self, int x, int y, int width, int height)
    {
        self->SetDimension(wxPoint(x, y), wxSize(width, height));
    }

    EXPORT wxSize* wxSizerItem_GetMinSize(wxSizerItem* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetMinSize();
        return text;
    }

    EXPORT void wxSizerItem_SetRatio(wxSizerItem* self, int width, int height)
    {
        self->SetRatio(width, height);
    }

    EXPORT void wxSizerItem_SetFloatRatio(wxSizerItem* self, float ratio)
    {
        self->SetRatio(ratio);
    }

    EXPORT float wxSizerItem_GetRatio(wxSizerItem* self)
    {
        return self->GetRatio();
    }

    EXPORT bool wxSizerItem_IsWindow(wxSizerItem* self)
    {
        return self->IsWindow();
    }

    EXPORT bool wxSizerItem_IsSizer(wxSizerItem* self)
    {
        return self->IsSizer();
    }

    EXPORT bool wxSizerItem_IsSpacer(wxSizerItem* self)
    {
        return self->IsSpacer();
    }

    EXPORT void wxSizerItem_SetInitSize(wxSizerItem* self, int x, int y)
    {
        self->SetInitSize(x, y);
    }

    EXPORT void wxSizerItem_SetFlag(wxSizerItem* self, int flag)
    {
        self->SetFlag(flag);
    }

    EXPORT void wxSizerItem_SetBorder(wxSizerItem* self, int border)
    {
        self->SetBorder(border);
    }

    EXPORT wxWindow* wxSizerItem_GetWindow(wxSizerItem* self)
    {
        return self->GetWindow();
    }

    // EWXWEXPORT(void,wxSizerItem_SetWindow)(wxSizerItem* self,wxWindow* window)
    EXPORT void wxSizerItem_AssignWindow(wxSizerItem* self, wxWindow* window)
    {
        self->AssignWindow(window);
    }

    EXPORT void* wxSizerItem_GetSizer(wxSizerItem* self)
    {
        return (void*) self->GetSizer();
    }

    // EWXWEXPORT(void,wxSizerItem_SetSizer)(wxSizerItem* self,wxSizer* sizer)
    EXPORT void wxSizerItem_AssignSizer(wxSizerItem* self, wxSizer* sizer)
    {
        self->AssignSizer(sizer);
    }

    EXPORT int wxSizerItem_GetFlag(wxSizerItem* self)
    {
        return self->GetFlag();
    }

    EXPORT int wxSizerItem_GetBorder(wxSizerItem* self)
    {
        return self->GetBorder();
    }

    EXPORT void* wxSizerItem_GetUserData(wxSizerItem* self)
    {
        return ((kwxDataObject*) self->GetUserData())->data;
    }

    EXPORT wxPoint* wxSizerItem_GetPosition(wxSizerItem* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT void wxSizerItem_Delete(wxSizerItem* self)
    {
        delete self;
    }

    EXPORT void wxSizerItem_DeleteWindows(wxSizerItem* self)
    {
        self->DeleteWindows();
    }

    EXPORT void wxSizerItem_DetachSizer(wxSizerItem* self)
    {
        self->DetachSizer();
    }

    EXPORT int wxSizerItem_GetProportion(wxSizerItem* self)
    {
        return self->GetProportion();
    }

    EXPORT wxRect* wxSizerItem_GetRect(wxSizerItem* self)
    {
        wxRect* rct = new wxRect();
        *rct = self->GetRect();
        return rct;
    }

    EXPORT wxSize* wxSizerItem_GetSpacer(wxSizerItem* self, void* width, void* height)
    {
        wxSize* text = new wxSize(0, 0);

        if (self->IsSpacer())
        {
            *text = self->GetSpacer();
        }
        return text;
    }

    EXPORT bool wxSizerItem_IsShown(wxSizerItem* self)
    {
        return self->IsShown();
    }

    EXPORT void wxSizerItem_SetProportion(wxSizerItem* self, int proportion)
    {
        self->SetProportion(proportion);
    }

    // EWXWEXPORT(void,wxSizerItem_SetSpacer)(wxSizerItem* self,int width,int height)
    EXPORT void wxSizerItem_AssignSpacer(wxSizerItem* self, int width, int height)
    {
        self->AssignSpacer(wxSize(width, height));
    }

    EXPORT void wxSizerItem_Show(wxSizerItem* self, int show)
    {
        self->Show(show);
    }

    EXPORT void wxSizer_AddWindow(wxSizer* self, wxWindow* window, int option, int flag, int border,
                                  void* userData)
    {
        self->Add(window, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_AddSizer(wxSizer* self, wxSizer* sizer, int option, int flag, int border,
                                 void* userData)
    {
        self->Add(sizer, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_Add(wxSizer* self, int width, int height, int option, int flag, int border,
                            void* userData)
    {
        self->Add(width, height, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_InsertWindow(wxSizer* self, int before, wxWindow* window, int option,
                                     int flag, int border, void* userData)
    {
        self->Insert(before, window, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_InsertSizer(wxSizer* self, int before, wxSizer* sizer, int option, int flag,
                                    int border, void* userData)
    {
        self->Insert(before, sizer, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_Insert(wxSizer* self, int before, int width, int height, int option,
                               int flag, int border, void* userData)
    {
        self->Insert(before, width, height, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_PrependWindow(wxSizer* self, wxWindow* window, int option, int flag,
                                      int border, void* userData)
    {
        self->Prepend(window, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_PrependSizer(wxSizer* self, wxSizer* sizer, int option, int flag,
                                     int border, void* userData)
    {
        self->Prepend(sizer, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_Prepend(wxSizer* self, int width, int height, int option, int flag,
                                int border, void* userData)
    {
        self->Prepend(width, height, option, flag, border, new kwxDataObject(userData));
    }

    EXPORT void wxSizer_SetMinSize(wxSizer* self, int width, int height)
    {
        self->SetMinSize(width, height);
    }

    EXPORT void wxSizer_SetItemMinSizeWindow(wxSizer* self, wxWindow* window, int width, int height)
    {
        self->SetItemMinSize(window, width, height);
    }

    EXPORT void wxSizer_SetItemMinSizeSizer(wxSizer* self, wxSizer* sizer, int width, int height)
    {
        self->SetItemMinSize(sizer, width, height);
    }

    EXPORT void wxSizer_SetItemMinSize(wxSizer* self, int pos, int width, int height)
    {
        self->SetItemMinSize(pos, width, height);
    }

    EXPORT wxSize* wxSizer_GetSize(wxSizer* self)
    {
        wxSize* s = new wxSize();
        *s = self->GetSize();
        return s;
    }

    EXPORT wxPoint* wxSizer_GetPosition(wxSizer* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT wxSize* wxSizer_GetMinSize(wxSizer* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetMinSize();
        return text;
    }

    EXPORT void wxSizer_RecalcSizes(wxSizer* self)
    {
        self->RecalcSizes();
    }

    EXPORT wxSize* wxSizer_CalcMin(wxSizer* self)
    {
        wxSize* text = new wxSize();
        *text = self->CalcMin();
        return text;
    }

    EXPORT void wxSizer_Layout(wxSizer* self)
    {
        self->Layout();
    }

    EXPORT void wxSizer_Fit(wxSizer* self, wxWindow* window)
    {
        self->Fit(window);
    }

    EXPORT void wxSizer_SetSizeHints(wxSizer* self, wxWindow* window)
    {
        self->SetSizeHints(window);
    }

    EXPORT int wxSizer_GetChildren(wxSizer* self, void* result, int count)
    {
        if (result && (unsigned int) count == self->GetChildren().GetCount())
        {
            int i = 0;
            wxSizerItemList::compatibility_iterator node = self->GetChildren().GetFirst();
            while (node)
            {
                ((void**) result)[i] = node->GetData();
                node = node->GetNext();
                ++i;
            }
            return i;
        }
        else
            return self->GetChildren().GetCount();
    }

    EXPORT void wxSizer_AddSpacer(wxSizer* self, int size)
    {
        self->AddSpacer(size);
    }

    EXPORT void wxSizer_AddStretchSpacer(wxSizer* self, int size)
    {
        self->AddStretchSpacer(size);
    }

    EXPORT void wxSizer_Clear(wxSizer* self, bool delete_windows)
    {
        self->Clear(delete_windows);
    }

    EXPORT bool wxSizer_DetachWindow(wxSizer* self, wxWindow* window)
    {
        return self->Detach(window);
    }

    EXPORT bool wxSizer_DetachSizer(wxSizer* self, wxSizer* sizer)
    {
        return self->Detach(sizer);
    }

    EXPORT bool wxSizer_Detach(wxSizer* self, int index)
    {
        return self->Detach((size_t) index);
    }

    EXPORT void wxSizer_FitInside(wxSizer* self, wxWindow* window)
    {
        self->FitInside(window);
    }

    EXPORT void* wxSizer_GetContainingWindow(wxSizer* self)
    {
        return (void*) self->GetContainingWindow();
    }

    EXPORT void* wxSizer_GetItemWindow(wxSizer* self, wxWindow* window, bool recursive)
    {
        return (void*) self->GetItem(window, recursive);
    }

    EXPORT void* wxSizer_GetItemSizer(wxSizer* self, wxSizer* sizer, bool recursive)
    {
        return (void*) self->GetItem(sizer, recursive);
    }

    EXPORT void* wxSizer_GetItem(wxSizer* self, int index)
    {
        return (void*) self->GetItem((size_t) index);
    }

    EXPORT bool wxSizer_HideWindow(wxSizer* self, wxWindow* window)
    {
        return self->Hide(window);
    }

    EXPORT bool wxSizer_HideSizer(wxSizer* self, wxSizer* sizer)
    {
        return self->Hide(sizer);
    }

    EXPORT bool wxSizer_Hide(wxSizer* self, int index)
    {
        return self->Hide((size_t) index);
    }

    EXPORT void* wxSizer_InsertSpacer(wxSizer* self, int index, int size)
    {
        return (void*) self->InsertSpacer((size_t) index, size);
    }

    EXPORT void* wxSizer_InsertStretchSpacer(wxSizer* self, int index, int prop)
    {
        return (void*) self->InsertStretchSpacer((size_t) index, prop);
    }

    EXPORT bool wxSizer_IsShownWindow(wxSizer* self, wxWindow* window)
    {
        return self->IsShown(window);
    }

    EXPORT bool wxSizer_IsShownSizer(wxSizer* self, wxSizer* sizer)
    {
        return self->IsShown(sizer);
    }

    EXPORT bool wxSizer_IsShown(wxSizer* self, size_t index)
    {
        return self->IsShown(index);
    }

    EXPORT void* wxSizer_PrependSpacer(wxSizer* self, int size)
    {
        return (void*) self->PrependSpacer(size);
    }

    EXPORT void* wxSizer_PrependStretchSpacer(wxSizer* self, int prop)
    {
        return (void*) self->PrependStretchSpacer(prop);
    }

    EXPORT bool wxSizer_ReplaceWindow(wxSizer* self, wxWindow* oldwin, wxWindow* newwin,
                                      bool recursive)
    {
        return self->Replace(oldwin, newwin, recursive);
    }

    EXPORT bool wxSizer_ReplaceSizer(wxSizer* self, wxSizer* oldsz, wxSizer* newsz, bool recursive)
    {
        return self->Replace(oldsz, newsz, recursive);
    }

    EXPORT bool wxSizer_Replace(wxSizer* self, int oldindex, wxSizerItem* newsz)
    {
        return self->Replace((size_t) oldindex, newsz);
    }

    /* Deprecated; replace with wxSizer_FitInside
    // EWXWEXPORT(void,wxSizer_SetVirtualSizeHints)(wxSizer* self,wxWindow* window)
    */

    EXPORT bool wxSizer_ShowWindow(wxSizer* self, wxWindow* window, bool show, bool recursive)
    {
        return self->Show(window, show, recursive);
    }

    EXPORT bool wxSizer_ShowSizer(wxSizer* self, wxSizer* sizer, bool show, bool recursive)
    {
        return self->Show(sizer, show, recursive);
    }

    EXPORT bool wxSizer_Show(wxSizer* self, int index, bool show)
    {
        return self->Show((size_t) index, show);
    }

    EXPORT void wxSizer_SetDimension(wxSizer* self, int x, int y, int width, int height)
    {
        self->SetDimension(x, y, width, height);
    }

    EXPORT void* wxGridSizer_Create(int rows, int cols, int vgap, int hgap)
    {
        return (void*) new wxGridSizer(rows, cols, vgap, hgap);
    }

    EXPORT void wxGridSizer_RecalcSizes(wxGridSizer* self)
    {
        self->RecalcSizes();
    }

    EXPORT wxSize* wxGridSizer_CalcMin(wxGridSizer* self)
    {
        wxSize* text = new wxSize();
        *text = self->CalcMin();
        return text;
    }

    EXPORT void wxGridSizer_SetCols(wxGridSizer* self, int cols)
    {
        self->SetCols(cols);
    }

    EXPORT void wxGridSizer_SetRows(wxGridSizer* self, int rows)
    {
        self->SetRows(rows);
    }

    EXPORT void wxGridSizer_SetVGap(wxGridSizer* self, int gap)
    {
        self->SetVGap(gap);
    }

    EXPORT void wxGridSizer_SetHGap(wxGridSizer* self, int gap)
    {
        self->SetHGap(gap);
    }

    EXPORT int wxGridSizer_GetCols(wxGridSizer* self)
    {
        return self->GetCols();
    }

    EXPORT int wxGridSizer_GetRows(wxGridSizer* self)
    {
        return self->GetRows();
    }

    EXPORT int wxGridSizer_GetVGap(wxGridSizer* self)
    {
        return self->GetVGap();
    }

    EXPORT int wxGridSizer_GetHGap(wxGridSizer* self)
    {
        return self->GetHGap();
    }

    EXPORT void* wxFlexGridSizer_Create(int rows, int cols, int vgap, int hgap)
    {
        return new wxFlexGridSizer(rows, cols, vgap, hgap);
    }

    EXPORT void wxFlexGridSizer_RecalcSizes(wxFlexGridSizer* self)
    {
        self->RecalcSizes();
    }

    EXPORT wxSize* wxFlexGridSizer_CalcMin(wxFlexGridSizer* self)
    {
        wxSize* text = new wxSize();
        *text = self->CalcMin();
        return text;
    }

    EXPORT void wxFlexGridSizer_AddGrowableRow(wxFlexGridSizer* self, size_t idx, int proportion)
    {
        self->AddGrowableRow(idx, proportion);
    }

    EXPORT void wxFlexGridSizer_RemoveGrowableRow(wxFlexGridSizer* self, size_t idx)
    {
        self->RemoveGrowableRow(idx);
    }

    EXPORT void wxFlexGridSizer_AddGrowableCol(wxFlexGridSizer* self, size_t idx, int proportion)
    {
        self->AddGrowableCol(idx, proportion);
    }

    EXPORT void wxFlexGridSizer_RemoveGrowableCol(wxFlexGridSizer* self, size_t idx)
    {
        self->RemoveGrowableCol(idx);
    }

    EXPORT void* wxBoxSizer_Create(int orient)
    {
        return (void*) new wxBoxSizer(orient);
    }

    EXPORT void wxBoxSizer_RecalcSizes(wxBoxSizer* self)
    {
        self->RecalcSizes();
    }

    EXPORT wxSize* wxBoxSizer_CalcMin(wxBoxSizer* self)
    {
        wxSize* text = new wxSize();
        *text = self->CalcMin();
        return text;
    }

    EXPORT int wxBoxSizer_GetOrientation(wxBoxSizer* self)
    {
        return self->GetOrientation();
    }

    EXPORT void* wxStaticBoxSizer_Create(wxStaticBox* box, int orient)
    {
        return (void*) new wxStaticBoxSizer(box, orient);
    }

    EXPORT void wxStaticBoxSizer_RecalcSizes(wxStaticBoxSizer* self)
    {
        self->RecalcSizes();
    }

    EXPORT wxSize* wxStaticBoxSizer_CalcMin(wxStaticBoxSizer* self)
    {
        wxSize* text = new wxSize();
        *text = self->CalcMin();
        return text;
    }

    EXPORT void* wxStaticBoxSizer_GetStaticBox(wxStaticBoxSizer* self)
    {
        return (void*) self->GetStaticBox();
    }
}
