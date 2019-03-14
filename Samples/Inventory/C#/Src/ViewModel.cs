#if NOESIS
using Noesis;
using System.Collections.Generic;
using System.ComponentModel;
#else
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
#endif

namespace Inventory
{
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

    public class Item
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public ItemCategory Category { get; set; }
        public int Life { get; set; }
        public int Mana { get; set; }
        public int Dps { get; set; }
        public int Armor { get; set; }
        public Rect Icon { get; set; }
    }

    public class NotifierBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public delegate void SlotItemChangedHandler(Slot slot, Item oldItem, Item newItem);
    public class Slot : NotifierBase
    {
        public string Name { get; set; }
        public ItemCategory AllowedCategory { get; set; }

        private Item _item;
        public Item Item
        {
            get { return _item; }
            set { if (_item != value) { OnItemChanged(_item, value); _item = value; OnPropertyChanged("Item"); } }
        }

        public event SlotItemChangedHandler ItemChanged;
        private void OnItemChanged(Item oldItem, Item newItem)
        {
            ItemChanged?.Invoke(this, oldItem, newItem);
        }

        private bool _isDragOver = false;
        public bool IsDragOver
        {
            get { return _isDragOver; }
            set { if (_isDragOver != value) { _isDragOver = value; OnPropertyChanged("IsDragOver"); } }
        }

        private bool _isDropAllowed = true;
        public bool IsDropAllowed
        {
            get { return _isDropAllowed; }
            set { if (_isDropAllowed != value) { _isDropAllowed = value; OnPropertyChanged("IsDropAllowed"); } }
        }

        public void UpdateIsDropAllowed()
        {
            if (ViewModel.Instance.DragSource == null && ViewModel.Instance.SelectedSlot == null)
            {
                IsDropAllowed = true;
            }
            else if (ViewModel.Instance.DragSource != null)
            {
                Slot sourceSlot = ViewModel.Instance.DragSource;
                Item sourceItem = ViewModel.Instance.DraggedItem;

                IsDropAllowed = IsItemAllowed(sourceItem) && sourceSlot.IsItemAllowed(Item);
            }
            else // ViewModel.Instance.SelectedSlot != null
            {
                Slot sourceSlot = ViewModel.Instance.SelectedSlot;

                IsDropAllowed = sourceSlot == this || (AllowedCategory == ItemCategory.All && 
                    (Item == null || Item.Category == sourceSlot.AllowedCategory));
            }
        }

        private bool IsItemAllowed(Item item)
        {
            return item == null || AllowedCategory == ItemCategory.All || AllowedCategory == item.Category;
        }

        private bool _isSelected = false;
        public bool IsSelected
        {
            get { return _isSelected; }
            set { if (_isSelected != value) { _isSelected = value; OnPropertyChanged("IsSelected"); } }
        }

        public bool MoveFocus { get; private set; }
        public void Focus()
        {
            MoveFocus = !MoveFocus;
            OnPropertyChanged("MoveFocus");
        }
    }

    public class Player : NotifierBase
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

        public string Name { get; set; }

        private int _life;
        public int Life
        {
            get { return _life; }
            set { if (_life != value) { _life = value; OnPropertyChanged("Life"); } }
        }

        private int _mana;
        public int Mana
        {
            get { return _mana; }
            set { if (_mana != value) { _mana = value; OnPropertyChanged("Mana"); } }
        }

        private int _dps;
        public int Dps
        {
            get { return _dps; }
            set { if (_dps != value) { _dps = value; OnPropertyChanged("Dps"); } }
        }

        private int _armor;
        public int Armor
        {
            get { return _armor; }
            set { if (_armor != value) { _armor = value; OnPropertyChanged("Armor"); } }
        }

        public Slot[] Slots { get; private set; }
        private string[] SlotNames = { "HEAD", "RING", "CHEST", "ARMS", "LEFT", "RIGHT", "LEGS", "FEET" };
        private ItemCategory[] SlotCategories =
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
    }

    public class ViewModel : NotifierBase
    {
        public ViewModel()
        {
            Instance = this;

            Platform = "PC"; // PC, XBOX, PS4

            Player = new Player { Name = "Morgan Hearson", Life = 1423, Mana = 345, Dps = 2164, Armor = 218 };
            Inventory = new List<Slot>();
            Items = new List<Item>();

            for (int i = 0; i < 45; ++i)
            {
                Inventory.Add(new Slot { Name = "Slot", AllowedCategory = ItemCategory.All });

                int x = 2 + (i % 8) * 62;
                int y = 2 + (i / 8) * 62;

                Items.Add(new Item
                {
                    Name = "Item",
                    Description = "Item description",
                    Category = GetCategory(i),
                    Life = i * 2,
                    Mana = i,
                    Dps = i * 9,
                    Armor = i * 3,
                    Icon = new Rect(x, y, 60, 60)
                });

                Inventory[i].Item = Items[i];
            }
        }

        private ItemCategory GetCategory(int index)
        {
            if (index < 13) return ItemCategory.Hand;
            if (index < 21) return ItemCategory.Ring;
            index -= 20;
            return (ItemCategory)(index % 5);
        }

        public static ViewModel Instance { get; private set; }

        public string Platform { get; private set; }

        public Player Player { get; private set; }

        public List<Slot> Inventory { get; private set; }

        public List<Item> Items { get; private set; }

        public void StartDragging(Slot source, Point position)
        {
            DraggedItemX = position.X;
            DraggedItemY = position.Y;
            DraggedItem = source.Item;
            DragSource = source;
            DragSource.Item = null;

            OnPropertyChanged("DraggedItem");

            UpdateDropSlots();
        }

        public void EndDragging(bool dropCancelled)
        {
            if (dropCancelled)
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

        private void UpdateDropSlots()
        {
            foreach (Slot s in Player.Slots)
            {
                s.UpdateIsDropAllowed();
            }

            foreach (Slot s in Inventory)
            {
                s.UpdateIsDropAllowed();
            }
        }

        public Slot DragSource { get; private set; }
        public Item DraggedItem { get; private set; }

        private double _draggedItemX = -100;
        public double DraggedItemX
        {
            get { return _draggedItemX; }
            set { if (_draggedItemX != value) { _draggedItemX = value; OnPropertyChanged("DraggedItemX"); } }
        }

        private double _draggedItemY = -100;
        public double DraggedItemY
        {
            get { return _draggedItemY; }
            set { if (_draggedItemY != value) { _draggedItemY = value; OnPropertyChanged("DraggedItemY"); } }
        }

        public Slot SelectedSlot { get; private set; }

        public void SelectSlot(Slot slot)
        {
            if (slot != null)
            {
                if (slot.AllowedCategory != ItemCategory.All)
                {
                    // Player slot, initiate a selection
                    slot.IsSelected = true;
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

                    SelectedSlot.IsSelected = false;
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
                    SelectedSlot.IsSelected = false;
                    SelectedSlot.Focus();
                    SelectedSlot = null;

                    UpdateDropSlots();
                }
            }
        }
    }
}
