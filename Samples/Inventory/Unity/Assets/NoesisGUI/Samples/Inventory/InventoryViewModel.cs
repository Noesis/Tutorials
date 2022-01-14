using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using Inventory;
using Noesis;

namespace Inventory
{
    public enum PlatformId
    {
        PC,
        XBOX,
        PS4
    }

    public enum ItemCategory
    {
        Head,
        Chest,
        Arms,
        Legs,
        Feet,
        Hand,
        Ring,
        All
    }

    [Serializable]
    public class Item
    {
        public string _name;
        public string Name { get => _name; }

        public string _description;
        public string Description { get => _description; }

        public ItemCategory _category;
        public ItemCategory Category { get => _category; }

        public int _life;
        public int Life { get => _life; }

        public int _mana;
        public int Mana { get => _mana; }

        public int _dps;
        public int Dps { get => _dps; }

        public int _armor;
        public int Armor { get => _armor; }

        public UnityEngine.Sprite _icon;
        public UnityEngine.Sprite Icon { get => _icon; }
    }

    [Serializable]
    public class Player : INotifyPropertyChanged
    {
        public Player()
        {
            Slots = new Slot[8];

            for (int i = 0; i < Slots.Length; ++i)
            {
                Slots[i] = new Slot { Name = SlotNames[i], AllowedCategory = SlotCategories[i] };
                Slots[i].ItemChanged += UpdateStats;
            }
        }

        public string _name;
        public string Name { get => _name; }

        public int _life;
        public int Life
        {
            get => _life;
            set { if (_life != value) { _life = value; OnPropertyChanged("Life"); } }
        }

        public int _mana;
        public int Mana
        {
            get => _mana;
            set { if (_mana != value) { _mana = value; OnPropertyChanged("Mana"); } }
        }

        public int _dps;
        public int Dps
        {
            get => _dps;
            set { if (_dps != value) { _dps = value; OnPropertyChanged("Dps"); } }
        }

        public int _armor;
        public int Armor
        {
            get => _armor;
            set { if (_armor != value) { _armor = value; OnPropertyChanged("Armor"); } }
        }

        public Slot[] Slots { get; private set; }

        private readonly string[] SlotNames =
        {
            "HEAD", "RING", "CHEST", "ARMS", "LEFT", "RIGHT", "LEGS", "FEET"
        };

        private readonly ItemCategory[] SlotCategories =
        {
            ItemCategory.Head, ItemCategory.Ring, ItemCategory.Chest, ItemCategory.Arms,
            ItemCategory.Hand, ItemCategory.Hand, ItemCategory.Legs, ItemCategory.Feet
        };

        private void UpdateStats(Slot slot, Item oldItem, Item newItem)
        {
            int life = Life;
            int mana = Mana;
            int dps = Dps;
            int armor = Armor;

            if (oldItem != null)
            {
                life -= oldItem.Life;
                mana -= oldItem.Mana;
                dps -= oldItem.Dps;
                armor -= oldItem.Armor;
            }
            if (newItem != null)
            {
                life += newItem.Life;
                mana += newItem.Mana;
                dps += newItem.Dps;
                armor += newItem.Armor;
            }

            Life = life;
            Mana = mana;
            Dps = dps;
            Armor = armor;
        }

        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        #endregion
    }

    public delegate void SlotItemChangedHandler(Slot slot, Item oldItem, Item newItem);
    public class Slot : INotifyPropertyChanged
    {
        public Slot()
        {
            IsDropAllowed = true;
        }

        public string Name { get; internal set; }
        public ItemCategory AllowedCategory { get; internal set; }

        private Item _item;
        public Item Item
        {
            get => _item;
            internal set { if (_item != value) { OnItemChanged(_item, value); _item = value; OnPropertyChanged("Item"); } }
        }

        public event SlotItemChangedHandler ItemChanged;
        private void OnItemChanged(Item oldItem, Item newItem)
        {
            ItemChanged?.Invoke(this, oldItem, newItem);
        }

        private bool _isDragOver = false;
        public bool IsDragOver
        {
            get => _isDragOver;
            set { if (_isDragOver != value) { _isDragOver = value; OnPropertyChanged("IsDragOver"); } }
        }

        public bool IsDropAllowed { get; private set; }

        public void UpdateIsDropAllowed(Slot selected, Slot source, Item draggedItem)
        {
            if (source == null && selected == null)
            {
                IsDropAllowed = true;
            }
            else if (source != null)
            {
                Slot sourceSlot = source;
                Item sourceItem = draggedItem;

                IsDropAllowed = AllowedCategory == sourceSlot.AllowedCategory ||
                    (IsItemAllowed(sourceItem) && sourceSlot.IsItemAllowed(Item));
            }
            else // selected != null
            {
                Slot sourceSlot = selected;

                IsDropAllowed = sourceSlot == this || (AllowedCategory == ItemCategory.All &&
                    Item != null && sourceSlot.AllowedCategory == Item.Category);
            }

            OnPropertyChanged("IsDropAllowed");
        }

        private bool IsItemAllowed(Item item)
        {
            return AllowedCategory == ItemCategory.All ||
                (item != null && AllowedCategory == item.Category);
        }

        public bool IsSelected { get; private set; }
        public void Select(bool selected)
        {
            IsSelected = selected;
            OnPropertyChanged("IsSelected");
        }

        public bool MoveFocus { get; private set; }
        public void Focus()
        {
            MoveFocus = !MoveFocus;
            OnPropertyChanged("MoveFocus");
        }

        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        #endregion
    }
}

public class InventoryViewModel : UnityEngine.MonoBehaviour, INotifyPropertyChanged
{
    public PlatformId _platform;
    public PlatformId Platform { get => _platform; }

    public Player _player;
    public Player Player { get => _player; }

    public NoesisEventCommand _startDragItem;
    public NoesisEventCommand _endDragItem;
    public NoesisEventCommand _dropItem;
    public NoesisEventCommand _selectSlot;

    public NoesisEventCommand StartDragItem { get => _startDragItem; }
    public NoesisEventCommand EndDragItem { get => _endDragItem; }
    public NoesisEventCommand DropItem { get => _dropItem; }
    public NoesisEventCommand SelectSlot { get => _selectSlot; }

    public List<Slot> Inventory { get; private set; }

    public List<Item> _items;
    public List<Item> Items { get => _items; }

    void Reset()
    {
        _platform = PlatformId.PC;

        _player = new Player
        {
            _name = "Morgan Hearson",
            _life = 1420,
            _mana = 345,
            _dps = 2170,
            _armor = 195
        };

        _items = new List<Item>();
        for (int i = 0; i < 45; ++i)
        {
            int x = 2 + (i % 8) * 62;
            int y = 2 + (i / 8) * 62;

            _items.Add(new Item
            {
                _name = $"Item {i}",
                _description = $"Item {i} description",
                _category = GetCategory(i),
                _life = i * 2,
                _mana = i,
                _dps = i * 9,
                _armor = i * 3
            });
        }
    }

    void Start()
    {
        Inventory = new List<Slot>();

        for (int i = 0; i < Items.Count; ++i)
        {
            Inventory.Add(new Slot
            {
                Name = "Slot",
                AllowedCategory = ItemCategory.All,
                Item = Items[i]
            });
        }

        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }

    private ItemCategory GetCategory(int index)
    {
        if (index < 13) return ItemCategory.Hand;
        if (index < 21) return ItemCategory.Ring;
        index -= 20;
        return (ItemCategory)(index % 5);
    }

    public bool CanExecuteOnStartDragItem(object param)
    {
        return DragSource == null && DraggedItem == null;
    }

    public void OnStartDragItem(object param)
    {
        DragSource = (Slot)param;
        DraggedItem = DragSource.Item;
        DragSource.Item = null;

        OnPropertyChanged("DraggedItem");

        UpdateDropSlots();
    }

    public void OnEndDragItem(object param)
    {
        bool dragSuccess = (bool)param;
        if (!dragSuccess)
        {
            // Drop was cancelled
            if (DragSource.AllowedCategory == ItemCategory.All)
            {
                // Restore item in source inventory slot
                DragSource.Item = DraggedItem;
            }
            else
            {
                // Source was a player slot, look for an empty space in inventory
                foreach (Slot slot in Inventory)
                {
                    if (slot.Item == null)
                    {
                        slot.Item = DraggedItem;
                        break;
                    }
                }
            }
        }

        DragSource = null;
        DraggedItem = null;

        OnPropertyChanged("DraggedItem");

        UpdateDropSlots();
    }

    public bool CanExecuteOnDropItem(object param)
    {
        Slot targetSlot = (Slot)param;
        return targetSlot.IsDropAllowed;
    }

    public void OnDropItem(object param)
    {
        Slot targetSlot = (Slot)param;

        // Move any item in target slot to the source slot
        DragSource.Item = targetSlot.Item;

        // Move dragged item to the target slot
        targetSlot.Item = DraggedItem;
    }

    public void OnSelectSlot(object param)
    {
        UpdateSelectedSlot((Slot)param);
    }

    private void UpdateDropSlots()
    {
        foreach (Slot s in Player.Slots)
        {
            s.UpdateIsDropAllowed(SelectedSlot, DragSource, DraggedItem);
        }

        foreach (Slot s in Inventory)
        {
            s.UpdateIsDropAllowed(SelectedSlot, DragSource, DraggedItem);
        }
    }

    public Slot DragSource { get; private set; }
    public Item DraggedItem { get; private set; }

    public Slot SelectedSlot { get; private set; }

    public void UpdateSelectedSlot(Slot slot)
    {
        if (slot != null)
        {
            if (slot.AllowedCategory != ItemCategory.All)
            {
                // Player slot, initiate a selection
                slot.Select(true);
                SelectedSlot = slot;
                UpdateDropSlots();

                // move focus to the first allowed slot in the inventory
                foreach (Slot s in Inventory)
                {
                    if (s.IsDropAllowed)
                    {
                        s.Focus();
                        break;
                    }
                }
            }
            else if (SelectedSlot != null)
            {
                // Inventory selection
                Item selectedItem = SelectedSlot.Item;
                SelectedSlot.Item = slot.Item;
                slot.Item = selectedItem;

                SelectedSlot.Select(false);
                SelectedSlot.Focus();
                SelectedSlot = null;

                UpdateDropSlots();
            }
        }
        else
        {
            // Cancel selection
            if (SelectedSlot != null)
            {
                SelectedSlot.Select(false);
                SelectedSlot.Focus();
                SelectedSlot = null;

                UpdateDropSlots();
            }
        }
    }

    private void OnValidate()
    {
        OnPropertyChanged("Platform");
        OnPropertyChanged("Player");

        if (Inventory != null)
        {
            Inventory = new List<Slot>(Inventory);
            OnPropertyChanged("Inventory");
        }
    }

    #region INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    void OnPropertyChanged(string name)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
    #endregion
}
