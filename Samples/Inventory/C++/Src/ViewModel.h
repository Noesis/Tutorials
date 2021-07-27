////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __INVENTORY_VIEWMODEL_H__
#define __INVENTORY_VIEWMODEL_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/INotifyPropertyChanged.h>
#include <NsDrawing/Rect.h>


namespace NoesisApp
{
class DelegateCommand;
}
namespace Noesis
{
class ImageSource;
}

namespace Inventory
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum ItemCategory
{
    ItemCategory_Head,
    ItemCategory_Chest,
    ItemCategory_Arms,
    ItemCategory_Legs,
    ItemCategory_Feet,
    ItemCategory_Hand,
    ItemCategory_Ring,
    ItemCategory_All
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Item final: public Noesis::BaseComponent
{
    Noesis::String name;
    Noesis::String description;
    ItemCategory category;
    int life;
    int mana;
    int dps;
    int armor;
    Noesis::Ptr<Noesis::ImageSource> icon;

    NS_DECLARE_REFLECTION(Item, BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class NotifierBase: public Noesis::BaseComponent, public Noesis::INotifyPropertyChanged
{
public:
    Noesis::PropertyChangedEventHandler& PropertyChanged() final;

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    void OnPropertyChanged(const char* propertyName);

private:
    Noesis::PropertyChangedEventHandler _changed;

    NS_DECLARE_REFLECTION(NotifierBase, BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Slot;
typedef Noesis::Delegate<void (Slot* slot, Item* oldItem, Item* newItem)> SlotItemChangedHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
class Slot: public NotifierBase
{
public:
    Slot(const char* name, ItemCategory allowedCategory);

    ItemCategory GetAllowedCategory() const;

    Item* GetItem() const;
    void SetItem(Item* item);

    SlotItemChangedHandler& ItemChanged();

    bool GetIsDragOver() const;
    void SetIsDragOver(bool over);

    bool GetIsDropAllowed() const;
    void UpdateIsDropAllowed(Slot* selected, Slot* source, Item* draggedItem);

    bool GetIsSelected() const;
    void SetIsSelected(bool select);

    bool GetMoveFocus() const;
    void Focus();

private:
    void OnItemChanged(Item* oldItem, Item* newItem);
    bool IsItemAllowed(Item* item) const;

private:
    Noesis::String _name;
    ItemCategory _allowedCategory;
    Noesis::Ptr<Item> _item;
    bool _isDragOver;
    bool _isDropAllowed;
    bool _isSelected;
    bool _moveFocus;

    SlotItemChangedHandler _itemChanged;

    NS_DECLARE_REFLECTION(Slot, NotifierBase)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Player final: public NotifierBase
{
public:
    Player(const char* name, int life, int mana, int dps, int armor);

    int GetLife() const;
    void SetLife(int value);

    int GetMana() const;
    void SetMana(int value);

    int GetDps() const;
    void SetDps(int value);

    int GetArmor() const;
    void SetArmor(int value);

    Noesis::ObservableCollection<Slot>* GetSlots() const;

private:
    void UpdateStats(Slot* slot, Item* oldItem, Item* newItem);

private:
    Noesis::String _name;

    int _life;
    int _mana;
    int _dps;
    int _armor;

    Noesis::Ptr<Noesis::ObservableCollection<Slot>> _slots;

    Noesis::PropertyChangedEventHandler _changed;

    NS_DECLARE_REFLECTION(Player, NotifierBase)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ViewModel final: public NotifierBase
{
public:
    ViewModel();

    const char* GetPlatform() const;

    Player* GetPlayer() const;
    Noesis::ObservableCollection<Slot>* GetInventory() const;
    Noesis::ObservableCollection<Item>* GetItems() const;

    NoesisApp::DelegateCommand* GetStartDragItem() const;
    NoesisApp::DelegateCommand* GetEndDragItem() const;
    NoesisApp::DelegateCommand* GetDropItem() const;
    NoesisApp::DelegateCommand* GetSelectSlot() const;

    Slot* GetDragSource() const;
    Item* GetDraggedItem() const;
    Slot* GetSelectedSlot() const;

private:
    bool OnCanStartDragItem(Noesis::BaseComponent* param);
    void OnStartDragItem(Noesis::BaseComponent* param);
    void OnEndDragItem(Noesis::BaseComponent* param);
    bool OnCanDropItem(Noesis::BaseComponent* param);
    void OnDropItem(Noesis::BaseComponent* param);
    void OnSelectSlot(Noesis::BaseComponent* param);

    void UpdateDropSlots();
    void UpdateSelectedSlot(Slot* slot);

private:
    Noesis::Ptr<Player> _player;
    Noesis::Ptr<Noesis::ObservableCollection<Slot>> _inventory;
    Noesis::Ptr<Noesis::ObservableCollection<Item>> _items;
    Noesis::Ptr<NoesisApp::DelegateCommand> _startDragItem;
    Noesis::Ptr<NoesisApp::DelegateCommand> _endDragItem;
    Noesis::Ptr<NoesisApp::DelegateCommand> _dropItem;
    Noesis::Ptr<NoesisApp::DelegateCommand> _selectSlot;
    Noesis::Ptr<Slot> _selectedSlot;
    Noesis::Ptr<Slot> _dragSource;
    Noesis::Ptr<Item> _draggedItem;

    NS_DECLARE_REFLECTION(ViewModel, NotifierBase)
};

}

NS_DECLARE_REFLECTION_ENUM(Inventory::ItemCategory)


#endif
