#include "wrapper.h"

wxDragResult ELJTextDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_data_func)
        return (wxDragResult) on_data_func(obj, (long) x, (long) y, (int) def);
    else
        return wxTextDropTarget::OnData(x, y, def);
}

bool ELJTextDropTarget::OnDrop(wxCoord x, wxCoord y)
{
    if (on_drop_func)
        return (bool) on_drop_func(obj, (long) x, (long) y);
    else
        return wxTextDropTarget::OnDrop(x, y);
}

wxDragResult ELJTextDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_enter_func)
        return (wxDragResult) on_enter_func(obj, (long) x, (long) y, (int) def);
    else
        return wxTextDropTarget::OnEnter(x, y, def);
}

wxDragResult ELJTextDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_drag_func)
        return (wxDragResult) on_drag_func(obj, (long) x, (long) y, (int) def);
    else
        return wxTextDropTarget::OnDragOver(x, y, def);
}

void ELJTextDropTarget::OnLeave()
{
    if (on_leave_func)
        on_leave_func(obj);
    else
        wxTextDropTarget::OnLeave();
}

wxDragResult ELJFileDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_data_func)
        return (wxDragResult) on_data_func(obj, (long) x, (long) y, (int) def);
    else
        return wxFileDropTarget::OnData(x, y, def);
}

bool ELJFileDropTarget::OnDrop(wxCoord x, wxCoord y)
{
    if (on_drop_func)
        return (bool) on_drop_func(obj, (long) x, (long) y);
    else
        return wxFileDropTarget::OnDrop(x, y);
}

wxDragResult ELJFileDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_enter_func)
        return (wxDragResult) on_enter_func(obj, (long) x, (long) y, (int) def);
    else
        return wxFileDropTarget::OnEnter(x, y, def);
}

wxDragResult ELJFileDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_drag_func)
        return (wxDragResult) on_drag_func(obj, (long) x, (long) y, (int) def);
    else
        return wxFileDropTarget::OnDragOver(x, y, def);
}

void ELJFileDropTarget::OnLeave()
{
    if (on_leave_func)
        on_leave_func(obj);
    else
        wxFileDropTarget::OnLeave();
}

wxDragResult ELJDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_data_func)
        return (wxDragResult) on_data_func(obj, (long) x, (long) y, (int) def);
    else
    {
        GetData();
        return def;
    }
}

bool ELJDropTarget::OnDrop(wxCoord x, wxCoord y)
{
    if (on_drop_func)
        return (bool) on_drop_func(obj, (long) x, (long) y);
    else
        return wxDropTarget::OnDrop(x, y);
}

wxDragResult ELJDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_enter_func)
        return (wxDragResult) on_enter_func(obj, (long) x, (long) y, (int) def);
    else
        return wxDropTarget::OnEnter(x, y, def);
}

wxDragResult ELJDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_drag_func)
        return (wxDragResult) on_drag_func(obj, (long) x, (long) y, (int) def);
    else
        return wxDropTarget::OnDragOver(x, y, def);
}

void ELJDropTarget::OnLeave()
{
    if (on_leave_func)
        on_leave_func(obj);
    else
        wxDropTarget::OnLeave();
}

bool ELJFileDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
    bool result = false;
    const char** arr = (const char**) malloc(sizeof(char*) * filenames.GetCount());

    for (unsigned int i = 0; i < filenames.GetCount(); i++)
        arr[i] = filenames.Item(i).utf8_str().data();

    result = func(obj, (long) x, (long) y, (void*) arr, (int) filenames.GetCount()) != 0;
    free(arr);

    return result;
}

bool ELJTextDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& text)
{
    return func(obj, (long) x, (long) y, (void*) text.utf8_str().data()) != 0;
}

extern "C"
{
    EXPORT void* ELJFileDropTarget_Create(void* self, void* _func)
    {
        return (void*) new ELJFileDropTarget(self, (FileDropFunc) _func);
    }

    EXPORT void ELJFileDropTarget_Delete(ELJFileDropTarget* self)
    {
        delete self;
    }

    EXPORT void* ELJTextDropTarget_Create(void* self, void* _func)
    {
        return (void*) new ELJTextDropTarget(self, (TextDropFunc) _func);
    }

    EXPORT void ELJTextDropTarget_Delete(ELJTextDropTarget* self)
    {
        delete self;
    }

    EXPORT void* TextDataObject_Create(wxString* _txt)
    {
        return (void*) new wxTextDataObject(*_txt);
    }

    EXPORT void TextDataObject_Delete(void* self)
    {
        delete (wxTextDataObject*) self;
    }

    EXPORT size_t TextDataObject_GetTextLength(void* self)
    {
        return ((wxTextDataObject*) self)->GetTextLength();
    }

    EXPORT wxString* TextDataObject_GetText(void* self)
    {
        wxString* result = new wxString();
        *result = ((wxTextDataObject*) self)->GetText();
        return result;
    }

    EXPORT void TextDataObject_SetText(void* _obj, wxString* strText)
    {
        ((wxTextDataObject*) _obj)->SetText(*strText);
    }

    EXPORT void* FileDataObject_Create(int _cnt, void* _lst)
    {
        wxFileDataObject* result = new wxFileDataObject();
        if (_cnt)
        {
            for (int i = 0; i < _cnt; i++)
                result->AddFile(((char**) _lst)[i]);
        }
        return (void*) result;
    }

    EXPORT void FileDataObject_Delete(void* self)
    {
        delete (wxFileDataObject*) self;
    }

    EXPORT void FileDataObject_AddFile(void* self, wxString* _fle)
    {
        ((wxFileDataObject*) self)->AddFile(*_fle);
    }

    EXPORT int FileDataObject_GetFilenames(void* self, void* _lst)
    {
        wxArrayString arr = ((wxFileDataObject*) self)->GetFilenames();
        if (_lst)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) _lst)[i] = strdup(arr.Item(i).utf8_str().data());
        }
        return arr.GetCount();
    }

    EXPORT void* BitmapDataObject_Create(wxBitmap* _bmp)
    {
        return (void*) new wxBitmapDataObject(*_bmp);
    }

    EXPORT void* BitmapDataObject_CreateEmpty()
    {
        return (void*) new wxBitmapDataObject();
    }

    EXPORT void BitmapDataObject_Delete(void* self)
    {
        delete (wxBitmapDataObject*) self;
    }

    EXPORT void BitmapDataObject_SetBitmap(void* self, wxBitmap* _bmp)
    {
        ((wxBitmapDataObject*) self)->SetBitmap(*_bmp);
    }

    EXPORT void BitmapDataObject_GetBitmap(void* self, wxBitmap* _bmp)
    {
        *_bmp = ((wxBitmapDataObject*) self)->GetBitmap();
    }

    EXPORT void* DropSource_Create(wxDataObject* data, wxWindow* win, void* copy, void* move,
                                   void* none)
    {
#if (wxCHECK_VERSION(2, 5, 0) && defined(__WXMAC__)) || defined(__WIN32__)
        return (void*) new wxDropSource(*data, win, *((wxCursor*) copy), *((wxCursor*) move),
                                        *((wxCursor*) none));
#else
        return (void*) new wxDropSource(*data, win, *((wxIcon*) copy), *((wxIcon*) move),
                                        *((wxIcon*) none));
#endif
    }

    EXPORT void DropSource_Delete(void* self)
    {
        delete (wxDropSource*) self;
    }

    EXPORT int DropSource_DoDragDrop(void* self, bool _move)
    {
        return (int) ((wxDropSource*) self)->DoDragDrop(_move);
    }

    EXPORT void* ELJDropTarget_Create(void* self)
    {
        return (void*) new ELJDropTarget(self);
    }

    EXPORT void ELJDropTarget_Delete(void* self)
    {
        delete (ELJDropTarget*) self;
    }

    EXPORT void ELJFileDropTarget_SetOnData(void* self, void* _func)
    {
        ((ELJFileDropTarget*) self)->SetOnData((DragThreeFunc) _func);
    }

    EXPORT void ELJFileDropTarget_SetOnDrop(void* self, void* _func)
    {
        ((ELJFileDropTarget*) self)->SetOnDrop((DragTwoFunc) _func);
    }

    EXPORT void ELJFileDropTarget_SetOnEnter(void* self, void* _func)
    {
        ((ELJFileDropTarget*) self)->SetOnEnter((DragThreeFunc) _func);
    }

    EXPORT void ELJFileDropTarget_SetOnDragOver(void* self, void* _func)
    {
        ((ELJFileDropTarget*) self)->SetOnDragOver((DragThreeFunc) _func);
    }

    EXPORT void ELJFileDropTarget_SetOnLeave(void* self, void* _func)
    {
        ((ELJFileDropTarget*) self)->SetOnLeave((DragZeroFunc) _func);
    }

    EXPORT void ELJTextDropTarget_SetOnData(void* self, void* _func)
    {
        ((ELJTextDropTarget*) self)->SetOnData((DragThreeFunc) _func);
    }

    EXPORT void ELJTextDropTarget_SetOnDrop(void* self, void* _func)
    {
        ((ELJTextDropTarget*) self)->SetOnDrop((DragTwoFunc) _func);
    }

    EXPORT void ELJTextDropTarget_SetOnEnter(void* self, void* _func)
    {
        ((ELJTextDropTarget*) self)->SetOnEnter((DragThreeFunc) _func);
    }

    EXPORT void ELJTextDropTarget_SetOnDragOver(void* self, void* _func)
    {
        ((ELJTextDropTarget*) self)->SetOnDragOver((DragThreeFunc) _func);
    }

    EXPORT void ELJTextDropTarget_SetOnLeave(void* self, void* _func)
    {
        ((ELJTextDropTarget*) self)->SetOnLeave((DragZeroFunc) _func);
    }

    EXPORT void ELJDropTarget_SetOnData(void* self, void* _func)
    {
        ((ELJDropTarget*) self)->SetOnData((DragThreeFunc) _func);
    }

    EXPORT void ELJDropTarget_SetOnDrop(void* self, void* _func)
    {
        ((ELJDropTarget*) self)->SetOnDrop((DragTwoFunc) _func);
    }

    EXPORT void ELJDropTarget_SetOnEnter(void* self, void* _func)
    {
        ((ELJDropTarget*) self)->SetOnEnter((DragThreeFunc) _func);
    }

    EXPORT void ELJDropTarget_SetOnDragOver(void* self, void* _func)
    {
        ((ELJDropTarget*) self)->SetOnDragOver((DragThreeFunc) _func);
    }

    EXPORT void ELJDropTarget_SetOnLeave(void* self, void* _func)
    {
        ((ELJDropTarget*) self)->SetOnLeave((DragZeroFunc) _func);
    }

    EXPORT void wxDropTarget_GetData(void* self)
    {
        ((wxDropTarget*) self)->GetData();
    }

    EXPORT void wxDropTarget_SetDataObject(void* self, void* _dat)
    {
        ((wxDropTarget*) self)->SetDataObject((wxDataObject*) _dat);
    }

    EXPORT void* ELJDragDataObject_Create(void* self, wxString* _fmt, void* _func1, void* _func2,
                                          void* _func3)
    {
        return (void*) new ELJDragDataObject(self, *(_fmt), (DataGetDataSize) _func1,
                                             (DataGetDataHere) _func2, (DataSetData) _func3);
    }

    EXPORT void ELJDragDataObject_Delete(void* self)
    {
        delete (ELJDragDataObject*) self;
    }

    EXPORT void* wxDataObjectComposite_Create()
    {
        return (void*) new wxDataObjectComposite();
    }

    EXPORT void wxDataObjectComposite_Delete(void* self)
    {
        delete (wxDataObjectComposite*) self;
    }

    EXPORT void wxDataObjectComposite_Add(void* self, void* _dat, bool _preferred)
    {
        ((wxDataObjectComposite*) self)->Add((wxDataObjectSimple*) _dat, _preferred);
    }
}
