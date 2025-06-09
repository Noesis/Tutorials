using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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

    public class Item
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public ItemCategory Category { get; set; }
        public int Life { get; set; }
        public int Mana { get; set; }
        public int Dps { get; set; }
        public int Armor { get; set; }
        public ImageSource Icon { get; set; }
    }

    public class NotifierBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }

    public delegate void SlotItemChangedHandler(Slot slot, Item oldItem, Item newItem);
    public class Slot : NotifierBase
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
            get { return _item; }
            internal set
            {
                if (_item != value)
                {
                    OnItemChanged(_item, value);
                    _item = value;
                    OnPropertyChanged("Item");
                }
            }
        }

        public event SlotItemChangedHandler ItemChanged;
        private void OnItemChanged(Item oldItem, Item newItem)
        {
            SlotItemChangedHandler handler = ItemChanged;
            if (handler != null)
            {
                handler(this, oldItem, newItem);
            }
        }

        private bool _isDragOver = false;
        public bool IsDragOver
        {
            get { return _isDragOver; }
            set
            {
                if (_isDragOver != value)
                {
                    _isDragOver = value;
                    OnPropertyChanged("IsDragOver");
                }
            }
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
    }

    public class ViewModel : NotifierBase
    {
        public ViewModel()
        {
            Platform = PlatformId.PC;

            Player = new Player { Name = "Morgan Hearson", Life = 1423, Mana = 345, Dps = 2164, Armor = 218 };
            Inventory = new List<Slot>();
            Items = new List<Item>();

            BitmapImage atlas = new BitmapImage(new Uri("pack://application:,,,/Inventory;component/Images/InventoryAtlas.png"));

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
                    Icon = new CroppedBitmap(atlas, new Int32Rect(x, y, 60, 60))
                }); ;

                Inventory[i].Item = Items[i];
            }

            StartDragItem = new DelegateCommand(this.OnCanStartDragItem, this.OnStartDragItem);
            EndDragItem = new DelegateCommand(this.OnEndDragItem);
            DropItem = new DelegateCommand(this.OnCanDropItem, this.OnDropItem);
            SelectSlot = new DelegateCommand(this.OnSelectSlot);
        }

        private ItemCategory GetCategory(int index)
        {
            if (index < 13) return ItemCategory.Hand;
            if (index < 21) return ItemCategory.Ring;
            index -= 20;
            return (ItemCategory)(index % 5);
        }

        public PlatformId Platform { get; private set; }

        public Player Player { get; private set; }

        public List<Slot> Inventory { get; private set; }

        public List<Item> Items { get; private set; }

        public DelegateCommand StartDragItem { get; private set; }
        public DelegateCommand EndDragItem { get; private set; }
        public DelegateCommand DropItem { get; private set; }
        public DelegateCommand SelectSlot { get; private set; }

        private bool OnCanStartDragItem(object param)
        {
            return DragSource == null && DraggedItem == null;
        }

        private void OnStartDragItem(object param)
        {
            DragSource = (Slot)param;
            DraggedItem = DragSource.Item;
            DragSource.Item = null;

            OnPropertyChanged("DraggedItem");

            UpdateDropSlots();
        }

        private void OnEndDragItem(object param)
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

        private bool OnCanDropItem(object param)
        {
            Slot targetSlot = (Slot)param;
            return targetSlot.IsDropAllowed;
        }

        private void OnDropItem(object param)
        {
            Slot targetSlot = (Slot)param;

            // Move any item in target slot to the source slot
            DragSource.Item = targetSlot.Item;

            // Move dragged item to the target slot
            targetSlot.Item = DraggedItem;
        }

        private void OnSelectSlot(object param)
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
    }
}
