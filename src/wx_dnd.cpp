#include "wrapper.h"

wxDragResult kwxTextDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_data_func)
        return (wxDragResult) on_data_func(obj, (long) x, (long) y, (int) def);
    else
        return wxTextDropTarget::OnData(x, y, def);
}

bool kwxTextDropTarget::OnDrop(wxCoord x, wxCoord y)
{
    if (on_drop_func)
        return (bool) on_drop_func(obj, (long) x, (long) y);
    else
        return wxTextDropTarget::OnDrop(x, y);
}

wxDragResult kwxTextDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_enter_func)
        return (wxDragResult) on_enter_func(obj, (long) x, (long) y, (int) def);
    else
        return wxTextDropTarget::OnEnter(x, y, def);
}

wxDragResult kwxTextDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_drag_func)
        return (wxDragResult) on_drag_func(obj, (long) x, (long) y, (int) def);
    else
        return wxTextDropTarget::OnDragOver(x, y, def);
}

void kwxTextDropTarget::OnLeave()
{
    if (on_leave_func)
        on_leave_func(obj);
    else
        wxTextDropTarget::OnLeave();
}

wxDragResult kwxFileDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_data_func)
        return (wxDragResult) on_data_func(obj, (long) x, (long) y, (int) def);
    else
        return wxFileDropTarget::OnData(x, y, def);
}

bool kwxFileDropTarget::OnDrop(wxCoord x, wxCoord y)
{
    if (on_drop_func)
        return (bool) on_drop_func(obj, (long) x, (long) y);
    else
        return wxFileDropTarget::OnDrop(x, y);
}

wxDragResult kwxFileDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_enter_func)
        return (wxDragResult) on_enter_func(obj, (long) x, (long) y, (int) def);
    else
        return wxFileDropTarget::OnEnter(x, y, def);
}

wxDragResult kwxFileDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_drag_func)
        return (wxDragResult) on_drag_func(obj, (long) x, (long) y, (int) def);
    else
        return wxFileDropTarget::OnDragOver(x, y, def);
}

void kwxFileDropTarget::OnLeave()
{
    if (on_leave_func)
        on_leave_func(obj);
    else
        wxFileDropTarget::OnLeave();
}

wxDragResult kwxDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_data_func)
        return (wxDragResult) on_data_func(obj, (long) x, (long) y, (int) def);
    else
    {
        GetData();
        return def;
    }
}

bool kwxDropTarget::OnDrop(wxCoord x, wxCoord y)
{
    if (on_drop_func)
        return (bool) on_drop_func(obj, (long) x, (long) y);
    else
        return wxDropTarget::OnDrop(x, y);
}

wxDragResult kwxDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_enter_func)
        return (wxDragResult) on_enter_func(obj, (long) x, (long) y, (int) def);
    else
        return wxDropTarget::OnEnter(x, y, def);
}

wxDragResult kwxDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (on_drag_func)
        return (wxDragResult) on_drag_func(obj, (long) x, (long) y, (int) def);
    else
        return wxDropTarget::OnDragOver(x, y, def);
}

void kwxDropTarget::OnLeave()
{
    if (on_leave_func)
        on_leave_func(obj);
    else
        wxDropTarget::OnLeave();
}

bool kwxFileDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
    bool result = false;
    const char** arr = (const char**) malloc(sizeof(char*) * filenames.GetCount());

    for (unsigned int i = 0; i < filenames.GetCount(); i++)
        arr[i] = filenames.Item(i).utf8_str().data();

    result = func(obj, (long) x, (long) y, (void*) arr, (int) filenames.GetCount()) != 0;
    free(arr);

    return result;
}

bool kwxTextDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& text)
{
    return func(obj, (long) x, (long) y, (void*) text.utf8_str().data()) != 0;
}

extern "C"
{
    EXPORT void* kwxFileDropTarget_Create(void* self, void* _func)
    {
        return (void*) new kwxFileDropTarget(self, (FileDropFunc) _func);
    }

    EXPORT void kwxFileDropTarget_Delete(kwxFileDropTarget* self)
    {
        delete self;
    }

    EXPORT void* kwxTextDropTarget_Create(void* self, void* _func)
    {
        return (void*) new kwxTextDropTarget(self, (TextDropFunc) _func);
    }

    EXPORT void kwxTextDropTarget_Delete(kwxTextDropTarget* self)
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

    EXPORT void* kwxDropTarget_Create(void* self)
    {
        return (void*) new kwxDropTarget(self);
    }

    EXPORT void kwxDropTarget_Delete(void* self)
    {
        delete (kwxDropTarget*) self;
    }

    EXPORT void kwxFileDropTarget_SetOnData(void* self, void* _func)
    {
        ((kwxFileDropTarget*) self)->SetOnData((DragThreeFunc) _func);
    }

    EXPORT void kwxFileDropTarget_SetOnDrop(void* self, void* _func)
    {
        ((kwxFileDropTarget*) self)->SetOnDrop((DragTwoFunc) _func);
    }

    EXPORT void kwxFileDropTarget_SetOnEnter(void* self, void* _func)
    {
        ((kwxFileDropTarget*) self)->SetOnEnter((DragThreeFunc) _func);
    }

    EXPORT void kwxFileDropTarget_SetOnDragOver(void* self, void* _func)
    {
        ((kwxFileDropTarget*) self)->SetOnDragOver((DragThreeFunc) _func);
    }

    EXPORT void kwxFileDropTarget_SetOnLeave(void* self, void* _func)
    {
        ((kwxFileDropTarget*) self)->SetOnLeave((DragZeroFunc) _func);
    }

    EXPORT void kwxTextDropTarget_SetOnData(void* self, void* _func)
    {
        ((kwxTextDropTarget*) self)->SetOnData((DragThreeFunc) _func);
    }

    EXPORT void kwxTextDropTarget_SetOnDrop(void* self, void* _func)
    {
        ((kwxTextDropTarget*) self)->SetOnDrop((DragTwoFunc) _func);
    }

    EXPORT void kwxTextDropTarget_SetOnEnter(void* self, void* _func)
    {
        ((kwxTextDropTarget*) self)->SetOnEnter((DragThreeFunc) _func);
    }

    EXPORT void kwxTextDropTarget_SetOnDragOver(void* self, void* _func)
    {
        ((kwxTextDropTarget*) self)->SetOnDragOver((DragThreeFunc) _func);
    }

    EXPORT void kwxTextDropTarget_SetOnLeave(void* self, void* _func)
    {
        ((kwxTextDropTarget*) self)->SetOnLeave((DragZeroFunc) _func);
    }

    EXPORT void kwxDropTarget_SetOnData(void* self, void* _func)
    {
        ((kwxDropTarget*) self)->SetOnData((DragThreeFunc) _func);
    }

    EXPORT void kwxDropTarget_SetOnDrop(void* self, void* _func)
    {
        ((kwxDropTarget*) self)->SetOnDrop((DragTwoFunc) _func);
    }

    EXPORT void kwxDropTarget_SetOnEnter(void* self, void* _func)
    {
        ((kwxDropTarget*) self)->SetOnEnter((DragThreeFunc) _func);
    }

    EXPORT void kwxDropTarget_SetOnDragOver(void* self, void* _func)
    {
        ((kwxDropTarget*) self)->SetOnDragOver((DragThreeFunc) _func);
    }

    EXPORT void kwxDropTarget_SetOnLeave(void* self, void* _func)
    {
        ((kwxDropTarget*) self)->SetOnLeave((DragZeroFunc) _func);
    }

    EXPORT void wxDropTarget_GetData(void* self)
    {
        ((wxDropTarget*) self)->GetData();
    }

    EXPORT void wxDropTarget_SetDataObject(void* self, void* _dat)
    {
        ((wxDropTarget*) self)->SetDataObject((wxDataObject*) _dat);
    }

    EXPORT void* kwxDragDataObject_Create(void* self, wxString* _fmt, void* _func1, void* _func2,
                                          void* _func3)
    {
        return (void*) new kwxDragDataObject(self, *(_fmt), (DataGetDataSize) _func1,
                                             (DataGetDataHere) _func2, (DataSetData) _func3);
    }

    EXPORT void kwxDragDataObject_Delete(void* self)
    {
        delete (kwxDragDataObject*) self;
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
