////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ViewModel.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsGui/BitmapImage.h>
#include <NsGui/CroppedBitmap.h>
#include <NsGui/Uri.h>
#include <NsDrawing/Int32Rect.h>
#include <NsApp/DelegateCommand.h>


using namespace Inventory;
using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
PropertyChangedEventHandler& NotifierBase::PropertyChanged()
{
    return _changed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NotifierBase::OnPropertyChanged(const char* propertyName)
{
    if (!_changed.Empty())
    {
        Symbol propId(propertyName);
        _changed(this, PropertyChangedEventArgs(propId));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Slot::Slot(const char* name, ItemCategory allowedCategory):
    _name(name), _allowedCategory(allowedCategory), _isDragOver(false), _isDropAllowed(true),
    _isSelected(false), _moveFocus(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ItemCategory Slot::GetAllowedCategory() const
{
    return _allowedCategory;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Item* Slot::GetItem() const
{
    return _item;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Slot::SetItem(Item* item)
{
    if (_item != item)
    {
        OnItemChanged(_item, item);
        _item.Reset(item);
        OnPropertyChanged("Item");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SlotItemChangedHandler& Slot::ItemChanged()
{
    return _itemChanged;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Slot::OnItemChanged(Item* oldItem, Item* newItem)
{
    _itemChanged(this, oldItem, newItem);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Slot::GetIsDragOver() const
{
    return _isDragOver;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Slot::SetIsDragOver(bool over)
{
    if (_isDragOver != over)
    {
        _isDragOver = over;
        OnPropertyChanged("IsDragOver");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Slot::GetIsDropAllowed() const
{
    return _isDropAllowed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Slot::UpdateIsDropAllowed(Slot* selected, Slot* source, Item* draggedItem)
{
    if (source == 0 && selected == 0)
    {
        _isDropAllowed = true;
    }
    else if (source != 0)
    {
        Slot* sourceSlot = source;
        Item* sourceItem = draggedItem;

        _isDropAllowed = _allowedCategory == sourceSlot->_allowedCategory ||
            (IsItemAllowed(sourceItem) && sourceSlot->IsItemAllowed(_item));
    }
    else // selected != 0
    {
        Slot* sourceSlot = selected;

        _isDropAllowed = sourceSlot == this || (_allowedCategory == ItemCategory_All &&
            _item != 0 && sourceSlot->_allowedCategory == _item->category);
    }

    OnPropertyChanged("IsDropAllowed");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Slot::IsItemAllowed(Item* item) const
{
    return _allowedCategory == ItemCategory_All ||
        (item != 0 && _allowedCategory == item->category);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
bool Slot::GetIsSelected() const
{
    return _isSelected;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Slot::SetIsSelected(bool select)
{
    if (_isSelected != select)
    {
        _isSelected = select;
        OnPropertyChanged("IsSelected");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Slot::GetMoveFocus() const
{
    return _moveFocus;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Slot::Focus()
{
    _moveFocus = !_moveFocus;
    OnPropertyChanged("MoveFocus");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(const char* name, int life, int mana, int dps, int armor):
    _name(name), _life(life), _mana(mana), _dps(dps), _armor(armor),
    _slots(*new ObservableCollection<Slot>())
{
    const char* slotNames[] = { "HEAD", "RING", "CHEST", "ARMS", "LEFT", "RIGHT", "LEGS", "FEET" };
    ItemCategory slotCategories[] =
    {
        ItemCategory_Head, ItemCategory_Ring, ItemCategory_Chest, ItemCategory_Arms,
        ItemCategory_Hand, ItemCategory_Hand, ItemCategory_Legs, ItemCategory_Feet
    };

    for (uint32_t i = 0; i < NS_COUNTOF(slotNames); ++i)
    {
        _slots->Add(MakePtr<Slot>(slotNames[i], slotCategories[i]));
        _slots->Get(i)->ItemChanged() += MakeDelegate(this, &Player::UpdateStats);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Player::GetLife() const
{
    return _life;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::SetLife(int value)
{
    if (_life != value)
    {
        _life = value;
        OnPropertyChanged("Life");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Player::GetMana() const
{
    return _mana;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::SetMana(int value)
{
    if (_mana != value)
    {
        _mana = value;
        OnPropertyChanged("Mana");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Player::GetDps() const
{
    return _dps;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::SetDps(int value)
{
    if (_dps != value)
    {
        _dps = value;
        OnPropertyChanged("Dps");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Player::GetArmor() const
{
    return _armor;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::SetArmor(int value)
{
    if (_armor != value)
    {
        _armor = value;
        OnPropertyChanged("Armor");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ObservableCollection<Slot>* Player::GetSlots() const
{
    return _slots;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::UpdateStats(Slot*, Item* oldItem, Item* newItem)
{
    int life = _life;
    int mana = _mana;
    int dps = _dps;
    int armor = _armor;

    if (oldItem != 0)
    {
        life -= oldItem->life;
        mana -= oldItem->mana;
        dps -= oldItem->dps;
        armor -= oldItem->armor;
    }
    if (newItem != 0)
    {
        life += newItem->life;
        mana += newItem->mana;
        dps += newItem->dps;
        armor += newItem->armor;
    }

    SetLife(life);
    SetMana(mana);
    SetDps(dps);
    SetArmor(armor);
}

namespace
{
ItemCategory GetCategory(int index)
{
    if (index < 13) return ItemCategory_Hand;
    if (index < 21) return ItemCategory_Ring;
    index -= 20;
    return (ItemCategory)(index % 5);
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ViewModel::ViewModel(): _player(*new Player("Morgan Hearson", 1423, 361, 2174, 218)),
    _inventory(*new ObservableCollection<Slot>()), _items(*new ObservableCollection<Item>())
{
    Ptr<BitmapImage> atlas = MakePtr<BitmapImage>("Images/InventoryAtlas.png");

    for (int i = 0; i < 45; ++i)
    {
        _inventory->Add(MakePtr<Slot>("Slot", ItemCategory_All));

        int x = 2 + (i % 8) * 62;
        int y = 2 + (i / 8) * 62;

        Ptr<Item> item = *new Item();
        item->name = "Item";
        item->description = "Item description";
        item->category = GetCategory(i);
        item->life = i * 2;
        item->mana = i;
        item->dps = i * 9;
        item->armor = i * 3;
        item->icon = MakePtr<CroppedBitmap>(atlas, Int32Rect(x, y, 60, 60));

        _items->Add(item);

        _inventory->Get(i)->SetItem(item);
    }

    _startDragItem = MakePtr<DelegateCommand>(
        MakeDelegate(this, &ViewModel::OnCanStartDragItem),
        MakeDelegate(this, &ViewModel::OnStartDragItem));
    _endDragItem = MakePtr<DelegateCommand>(MakeDelegate(this, &ViewModel::OnEndDragItem));
    _dropItem = MakePtr<DelegateCommand>(
        MakeDelegate(this, &ViewModel::OnCanDropItem),
        MakeDelegate(this, &ViewModel::OnDropItem));
    _selectSlot = MakePtr<DelegateCommand>(MakeDelegate(this, &ViewModel::OnSelectSlot));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ViewModel::GetPlatform() const
{
#if defined(NS_PLATFORM_XBOX_ONE) || defined(NS_PLATFORM_NX)
    return "XBOX";
#elif defined(NS_PLATFORM_PS4) || defined(NS_PLATFORM_PS5)
    return "PS4";
#else
    return "PC";
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Player* ViewModel::GetPlayer() const
{
    return _player;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ObservableCollection<Slot>* ViewModel::GetInventory() const
{
    return _inventory;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ObservableCollection<Item>* ViewModel::GetItems() const
{
    return _items;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::OnCanStartDragItem(BaseComponent*)
{
    return _dragSource == 0 && _selectedSlot == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnStartDragItem(BaseComponent* param)
{
    Slot* source = (Slot*)param;
    _draggedItem.Reset(source->GetItem());
    _dragSource.Reset(source);
    _dragSource->SetItem(0);

    OnPropertyChanged("DraggedItem");

    UpdateDropSlots();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnEndDragItem(BaseComponent* param)
{
    bool dragSuccess = Boxing::Unbox<bool>(param);
    if (!dragSuccess)
    {
        // Drop was cancelled
        if (_dragSource->GetAllowedCategory() == ItemCategory_All)
        {
            // Restore item in source inventory slot
            _dragSource->SetItem(_draggedItem);
        }
        else
        {
            // Source was a player slot, look for an empty space in inventory
            int numSlots = _inventory->Count();
            for (int i = 0; i < numSlots; ++i)
            {
                Slot* slot = _inventory->Get(i);
                if (slot->GetItem() == 0)
                {
                    slot->SetItem(_draggedItem);
                    break;
                }
            }
        }
    }

    _dragSource.Reset();
    _draggedItem.Reset();

    OnPropertyChanged("DraggedItem");

    UpdateDropSlots();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ViewModel::OnCanDropItem(Noesis::BaseComponent* param)
{
    Slot* targetSlot = (Slot*)param;
    return targetSlot->GetIsDropAllowed();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnDropItem(BaseComponent* param)
{
    Slot* targetSlot = (Slot*)param;

    // Move any item in target slot to the source slot
    _dragSource->SetItem(targetSlot->GetItem());

    // Move dragged item to the target slot
    targetSlot->SetItem(_draggedItem);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::OnSelectSlot(BaseComponent* param)
{
    UpdateSelectedSlot((Slot*)param);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::UpdateDropSlots()
{
    ObservableCollection<Slot>* playerSlots = _player->GetSlots();
    int numPlayerSlots = playerSlots->Count();
    for (int i = 0; i < numPlayerSlots; ++i)
    {
        playerSlots->Get(i)->UpdateIsDropAllowed(_selectedSlot, _dragSource, _draggedItem);
    }

    int numInventorySlots = _inventory->Count();
    for (int i = 0; i < numInventorySlots; ++i)
    {
        _inventory->Get(i)->UpdateIsDropAllowed(_selectedSlot, _dragSource, _draggedItem);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ViewModel::UpdateSelectedSlot(Slot* slot)
{
    if (slot != 0)
    {
        if (slot->GetAllowedCategory() != ItemCategory_All)
        {
            // Player slot, initiate a selection
            slot->SetIsSelected(true);
            _selectedSlot.Reset(slot);
            UpdateDropSlots();

            // move focus to the first allowed slot in the inventory
            int numSlots = _inventory->Count();
            for (int i = 0; i < numSlots; ++i)
            {
                Slot* s = _inventory->Get(i);
                if (s->GetIsDropAllowed())
                {
                    s->Focus();
                    break;
                }
            }
        }
        else if (_selectedSlot != 0)
        {
            // Inventory selection
            Item* selectedItem = _selectedSlot->GetItem();
            _selectedSlot->SetItem(slot->GetItem());
            slot->SetItem(selectedItem);

            _selectedSlot->SetIsSelected(false);
            _selectedSlot->Focus();
            _selectedSlot.Reset();

            UpdateDropSlots();
        }
    }
    else
    {
        // Cancel selection
        if (_selectedSlot != 0)
        {
            _selectedSlot->SetIsSelected(false);
            _selectedSlot->Focus();
            _selectedSlot.Reset();

            UpdateDropSlots();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetStartDragItem() const
{
    return _startDragItem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetEndDragItem() const
{
    return _endDragItem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetDropItem() const
{
    return _dropItem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DelegateCommand* ViewModel::GetSelectSlot() const
{
    return _selectSlot;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Slot* ViewModel::GetDragSource() const
{
    return _dragSource;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Item* ViewModel::GetDraggedItem() const
{
    return _draggedItem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Slot* ViewModel::GetSelectedSlot() const
{
    return _selectedSlot;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ViewModel)
{
    NsProp("Platform", &ViewModel::GetPlatform);
    NsProp("Player", &ViewModel::GetPlayer);
    NsProp("Inventory", &ViewModel::GetInventory);
    NsProp("StartDragItem", &ViewModel::GetStartDragItem);
    NsProp("EndDragItem", &ViewModel::GetEndDragItem);
    NsProp("DropItem", &ViewModel::GetDropItem);
    NsProp("SelectSlot", &ViewModel::GetSelectSlot);
    NsProp("DraggedItem", &ViewModel::GetDraggedItem);
}

NS_IMPLEMENT_REFLECTION_ENUM(ItemCategory, "Inventory.ItemCategory")
{
    NsVal("Head", ItemCategory_Head);
    NsVal("Chest", ItemCategory_Chest);
    NsVal("Arms", ItemCategory_Arms);
    NsVal("Legs", ItemCategory_Legs);
    NsVal("Feet", ItemCategory_Feet);
    NsVal("Hand", ItemCategory_Hand);
    NsVal("Ring", ItemCategory_Ring);
    NsVal("All", ItemCategory_All);
}

NS_IMPLEMENT_REFLECTION(Item)
{
    NsProp("Name", &Item::name);
    NsProp("Description", &Item::description);
    NsProp("Category", &Item::category);
    NsProp("Life", &Item::life);
    NsProp("Mana", &Item::mana);
    NsProp("Dps", &Item::dps);
    NsProp("Armor", &Item::armor);
    NsProp("Icon", &Item::icon);
}

NS_IMPLEMENT_REFLECTION(NotifierBase)
{
    NsImpl<INotifyPropertyChanged>();
}

NS_IMPLEMENT_REFLECTION(Slot)
{
    NsProp("Name", &Slot::_name);
    NsProp("AllowedCategory", &Slot::GetAllowedCategory);
    NsProp("Item", &Slot::GetItem);
    NsProp("IsDragOver", &Slot::GetIsDragOver, &Slot::SetIsDragOver);
    NsProp("IsDropAllowed", &Slot::GetIsDropAllowed);
    NsProp("IsSelected", &Slot::GetIsSelected);
    NsProp("MoveFocus", &Slot::GetMoveFocus);
}

NS_IMPLEMENT_REFLECTION(Player)
{
    NsImpl<INotifyPropertyChanged>();

    NsProp("Name", &Player::_name);

    NsProp("Life", &Player::GetLife, &Player::SetLife);
    NsProp("Mana", &Player::GetMana, &Player::SetMana);
    NsProp("Dps", &Player::GetDps, &Player::SetDps);
    NsProp("Armor", &Player::GetArmor, &Player::SetArmor);

    NsProp("Slots", &Player::GetSlots);
}

NS_END_COLD_REGION
