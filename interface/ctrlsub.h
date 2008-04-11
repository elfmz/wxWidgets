/////////////////////////////////////////////////////////////////////////////
// Name:        ctrlsub.h
// Purpose:     interface of wxControlWithItems
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


/**
    @wxheader{ctrlsub.h}

    wxItemContainer defines an interface which is implemented by all controls
    which have string subitems each of which may be selected.

    It is decomposed in wxItemContainerImmutable which omits all methods
    adding/removing items and is used by wxRadioBox and wxItemContainer itself.

    Note that this is not a control, it's a mixin interface that classes
    have to derive from in addition to wxControl or wxWindow.

    Examples: wxListBox, wxCheckListBox, wxChoice and wxComboBox (which
    implements an extended interface deriving from this one)

    @library{wxcore}
    @category{ctrl}

    @see wxControlWithItems, wxItemContainer
*/
class wxItemContainerImmutable
{
public:
    /// Constructor
    wxItemContainerImmutable();

    //@{

    /**
        Returns the number of items in the control.

        @see IsEmpty()
    */
    virtual unsigned int GetCount() const;

    /**
        Returns @true if the control is empty or @false if it has some items.

        @see GetCount()
    */
    bool IsEmpty() const;


    /**
        Returns the label of the item with the given index.

        @param n
            The zero-based index.

        @returns The label of the item or an empty string if the position was
                 invalid.
    */
    virtual wxString GetString(unsigned int n) const;

    /**
        Returns the array of the labels of all items in the control.
    */
    wxArrayString GetStrings() const;

    /**
        Sets the label for the given item.

        @param n
            The zero-based item index.
        @param string
            The label to set.
    */
    virtual void SetString(unsigned int n, const wxString& s);

    /**
        Finds an item whose label matches the given string.

        @param string
            String to find.
        @param caseSensitive
            Whether search is case sensitive (default is not).

        @returns The zero-based position of the item, or wxNOT_FOUND if the
                 string was not found.
    */
    virtual int FindString(const wxString& s, bool bCase = false) const;

    //@}

    // selection
    // ---------
    //@{

    /**
        Sets the selection to the given item @a n or removes the selection
        entirely if @a n == @c wxNOT_FOUND.

        Note that this does not cause any command events to be emitted nor does
        it deselect any other items in the controls which support multiple
        selections.

        @param n
            The string position to select, starting from zero.

        @see SetString(), SetStringSelection()
    */
    virtual void SetSelection(int n);

    /**
        Returns the index of the selected item or @c wxNOT_FOUND if no item is
        selected.

        @returns The position of the current selection.

        @remarks This method can be used with single selection list boxes only,
                 you should use wxListBox::GetSelections() for the list
                 boxes with wxLB_MULTIPLE style.

        @see SetSelection(), GetStringSelection()
    */
    virtual int GetSelection() const;

    /**
        Selects the item with the specified string in the control. This doesn't
        cause any command events to be emitted.

        @param string
            The string to select.

        @returns @true if the specified string has been selected, @false if it
                 wasn't found in the control.
    */
    bool SetStringSelection(const wxString& string);

    /**
        Returns the label of the selected item or an empty string if no item is
        selected.

        @see GetSelection()
    */
    virtual wxString GetStringSelection() const;

    /**
        This is the same as SetSelection() and exists only because it is
        slightly more natural for controls which support multiple selection.
    */
    void Select(int n);

    //@}
};


/**
    @wxheader{ctrlsub.h}

    This class is an abstract base class for some wxWidgets controls which
    contain several items such as wxListBox, wxCheckListBox, wxComboBox or
    wxChoice. It defines an interface which is implemented by all controls
    which have string subitems each of which may be selected.

    wxItemContainer extends wxItemContainerImmutable interface with methods
    for adding/removing items.

    It defines the methods for accessing the controls items and although each
    of the derived classes implements them differently, they still all conform
    to the same interface.

    The items in a wxItemContainer have (non-empty) string labels and,
    optionally, client data associated with them. Client data may be of two
    different kinds: either simple untyped (@c void *) pointers which are
    simply stored by the control but not used in any way by it, or typed
    pointers (wxClientData*) which are owned by the control meaning that the
    typed client data (and only it) will be deleted when an item is deleted
    using wxItemContainer::Delete() or the entire control is cleared using
    wxItemContainer::Clear(), which also happens when it is destroyed.

    Finally note that in the same control all items must have client data of
    the same type (typed or untyped), if any. This type is determined by the
    first call to wxItemContainer::Append() (the version with client data
    pointer) or wxItemContainer::SetClientData().

    Note that this is not a control, it's a mixin interface that classes
    have to derive from in addition to wxControl or wxWindow. Convenience
    class wxControlWithItems is provided for this purpose.

    @library{wxcore}
    @category{ctrl}

    @see wxControlWithItems, wxItemContainerImmutable
*/
class wxItemContainer : public wxItemContainerImmutable
{
public:
    //@{

    /**
        Appends item into the control.

        @param item
            String to add.

        @returns The return value is the index of the newly inserted item.
                 Note that this may be different from the last one if the
                 control is sorted (e.g. has @c wxLB_SORT or @c wxCB_SORT
                 style).
    */
    int Append(const wxString& item);

    /**
        Appends item into the control.

        @param item
            String to add.
        @param clientData
            Pointer to client data to associate with the new item.

        @returns The return value is the index of the newly inserted item.
                 Note that this may be different from the last one if the
                 control is sorted (e.g. has @c wxLB_SORT or @c wxCB_SORT
                 style).
    */
    int Append(const wxString& item, void* clientData);

    /**
        Appends item into the control.

        @param item
            String to add.
        @param clientData
            Pointer to client data to associate with the new item.

        @returns The return value is the index of the newly inserted item.
                 Note that this may be different from the last one if the
                 control is sorted (e.g. has @c wxLB_SORT or @c wxCB_SORT
                 style).
    */
    int Append(const wxString& item, wxClientData* clientData);

    /**
        Appends several items at once into the control.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param items
            Array of strings to insert.
    */
    void Append(const wxArrayString& items);

    /**
        Appends several items at once into the control.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param items
            Array of strings to insert.
        @param clientData
            Array of client data pointers of the same size as @a items to
            associate with the new items.
    */
    void Append(const wxArrayString& items, void **clientData);

    /**
        Appends several items at once into the control.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param items
            Array of strings to insert.
        @param clientData
            Array of client data pointers of the same size as @a items to
            associate with the new items.
    */
    void Append(const wxArrayString& items, wxClientData **clientData);

    /**
        Appends several items at once into the control.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
    */
    void Append(unsigned int n, const wxString* items);

    /**
        Appends several items at once into the control.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param clientData
            Array of client data pointers of size @a n to associate with the
            new items.
    */
    void Append(unsigned int n, const wxString* items,
                void** clientData);

    /**
        Appends several items at once into the control.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param clientData
            Array of client data pointers of size @a n to associate with the
            new items.
    */
    void Append(unsigned int n, const wxString* items,
                wxClientData** clientData);
    //@}

    /**
        Removes all items from the control.
        Clear() also deletes the client data of the existing items if it is
        owned by the control.
    */
    void Clear();

    /**
        Deletes an item from the control.

        The client data associated with the item will be also deleted if it is
        owned by the control.  Note that it is an error (signalled by an assert
        failure in debug builds) to remove an item with the index negative or
        greater or equal than the number of items in the control.

        @param n
            The zero-based item index.

        @see Clear()
    */
    void Delete(unsigned int n);

    //@{

    /**
        Returns a pointer to the client data associated with the given item (if
        any).  It is an error to call this function for a control which doesn't
        have untyped client data at all although it is OK to call it even if
        the given item doesn't have any client data associated with it (but
        other items do).

        @param n
            The zero-based position of the item.

        @returns A pointer to the client data, or @NULL if not present.
    */
    void* GetClientData(unsigned int n) const;

    /**
        Returns a pointer to the client data associated with the given item (if
        any).  It is an error to call this function for a control which doesn't
        have typed client data at all although it is OK to call it even if the
        given item doesn't have any client data associated with it (but other
        items do).

        @param n
            The zero-based position of the item.

        @returns A pointer to the client data, or @NULL if not present.
    */
    wxClientData* GetClientObject(unsigned int n) const;

    /**
        Associates the given untyped client data pointer with the given item.
        Note that it is an error to call this function if any typed client data
        pointers had been associated with the control items before.

        @param n
            The zero-based item index.
        @param data
            The client data to associate with the item.
    */
    void SetClientData(unsigned int n, void* data);

    /**
        Associates the given typed client data pointer with the given item: the
        @a data object will be deleted when the item is deleted (either
        explicitly by using Delete() or implicitly when the control itself is
        destroyed).  Note that it is an error to call this function if any
        untyped client data pointers had been associated with the control items
        before.

        @param n
            The zero-based item index.
        @param data
            The client data to associate with the item.
    */
    void SetClientObject(unsigned int n, wxClientData* data);

    //@}

    //@{

    /**
        Inserts item into the control.

        @param item
            String to add.
        @param pos
            Position to insert item before, zero based.

        @returns The return value is the index of the newly inserted item.
                 If the insertion failed for some reason, -1 is returned.
    */
    int Insert(const wxString& item, unsigned int pos);

    /**
        Inserts item into the control.

        @param item
            String to add.
        @param pos
            Position to insert item before, zero based.
        @param clientData
            Pointer to client data to associate with the new item.

        @returns The return value is the index of the newly inserted item.
                 If the insertion failed for some reason, -1 is returned.
    */
    int Insert(const wxString& item, unsigned int pos, void* clientData);

    /**
        Inserts item into the control.

        @param item
            String to add.
        @param pos
            Position to insert item before, zero based.
        @param clientData
            Pointer to client data to associate with the new item.

        @returns The return value is the index of the newly inserted item.
                 If the insertion failed for some reason, -1 is returned.
    */
    int Insert(const wxString& item, unsigned int pos,
               wxClientData* clientData);

    /**
        Inserts several items at once into the control.

        Notice that calling this method is usually much faster than inserting
        them one by one if you need to insert a lot of items.

        @param items
            Array of strings to insert.
        @param pos
            Position to insert the items before, zero based.
    */
    void Insert(const wxArrayString& items, unsigned int pos);

    /**
        Inserts several items at once into the control.

        Notice that calling this method is usually much faster than inserting
        them one by one if you need to insert a lot of items.

        @param items
            Array of strings to insert.
        @param pos
            Position to insert the items before, zero based.
        @param clientData
            Array of client data pointers of the same size as @a items to
            associate with the new items.
    */
    void Insert(const wxArrayString& items, unsigned int pos,
                void **clientData);

    /**
        Inserts several items at once into the control.

        Notice that calling this method is usually much faster than inserting
        them one by one if you need to insert a lot of items.

        @param items
            Array of strings to insert.
        @param pos
            Position to insert the items before, zero based.
        @param clientData
            Array of client data pointers of the same size as @a items to
            associate with the new items.
    */
    void Insert(const wxArrayString& items, unsigned int pos,
                wxClientData **clientData);

    /**
        Inserts several items at once into the control.

        Notice that calling this method is usually much faster than inserting
        them one by one if you need to insert a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param pos
            Position to insert the items before, zero based.
    */
    void Insert(unsigned int n, const wxString* items,
                unsigned int pos);

    /**
        Inserts several items at once into the control.

        Notice that calling this method is usually much faster than inserting
        them one by one if you need to insert a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param pos
            Position to insert the new items before, zero based.
        @param clientData
            Array of client data pointers of size @a n to associate with the
            new items.
    */
    void Insert(unsigned int n, const wxString* items,
                unsigned int pos,
                void** clientData);

    /**
        Inserts several items at once into the control.

        Notice that calling this method is usually much faster than inserting
        them one by one if you need to insert a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param pos
            Position to insert the new items before, zero based.
        @param clientData
            Array of client data pointers of size @a n to associate with the
            new items.
    */
    void Insert(unsigned int n, const wxString* items,
                unsigned int pos,
                wxClientData** clientData);
    //@}

    //@{
    /**
        Replaces the current control contents with the given items.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param items
            Array of strings to insert.
    */
    void Set(const wxArrayString& items);

    /**
        Replaces the current control contents with the given items.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param items
            Array of strings to insert.
        @param clientData
            Array of client data pointers of the same size as @a items to
            associate with the new items.
    */
    void Set(const wxArrayString& items, void **clientData);

    /**
        Replaces the current control contents with the given items.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param items
            Array of strings to insert.
        @param clientData
            Array of client data pointers of the same size as @a items to
            associate with the new items.
    */
    void Set(const wxArrayString& items, wxClientData **clientData);

    /**
        Replaces the current control contents with the given items.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
    */
    void Set(unsigned int n, const wxString* items);

    /**
        Replaces the current control contents with the given items.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param clientData
            Array of client data pointers of size @a n to associate with the
            new items.
    */
    void Set(unsigned int n, const wxString* items, void** clientData);

    /**
        Replaces the current control contents with the given items.

        Notice that calling this method is usually much faster than appending
        them one by one if you need to add a lot of items.

        @param n
            Number of items in the @a items array.
        @param items
            Array of strings of size @a n.
        @param clientData
            Array of client data pointers of size @a n to associate with the
            new items.
    */
    void Set(unsigned int n, const wxString* items, wxClientData** clientData);
    //@}
};


/**
    @class wxControlWithItems
    @wxheader{ctrlsub.h}

    This is convenience class that derives from both wxControl and
    wxItemContainer. It is used as basis for some wxWidgets controls
    (wxChoice and wxListBox).

    @library{wxcore}
    @category{ctrl}

    @see wxItemContainer, wxItemContainerImmutable
*/
class wxControlWithItems : public wxControl, public wxItemContainer
{
};

