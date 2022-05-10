#include <efi.h>
#include <libefi.h>

typedef struct menu
{
  UINTN x, y;
  UINTN width, heigth;
  CHAR16 **items;
  UINTN selected_item;
} menu_t;

static void exit(UINTN status)
{
  BS->Exit(IH, 1, 0, NULL);
}

static void error(CHAR16 *string)
{
  puts(string);
  exit(1);
}

static void draw_box(UINTN x, UINTN y, UINTN width, UINTN heigth)
{
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *conout;

  conout = ST->ConOut;
  
  UINTN i, cy = y;
  for(i = 0; i < heigth - 2; i++)
  {
    conout->SetCursorPosition(conout, x, ++cy);
    putchar(L'|');
    conout->SetCursorPosition(conout, x + width - 1, cy);
    putchar(L'|');
  }

  conout->SetCursorPosition(conout, x, y);
  for(i = 0; i < width * 2; i++)
  {
    
    if(i == width)
      conout->SetCursorPosition(conout, x, y + heigth - 1);
    
    if(i == 0 || i == width - 1 ||
       i == width || i == width * 2 - 1)
      putchar(L'+');
    else
      putchar(L'-');
  }
}

void menu_add_item(menu_t *menu, UINTN item)
{
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *conout = ST->ConOut;
  
  conout->SetCursorPosition(conout, menu->x + 1, menu->y + 1 + item);
  printf(menu->items[item]);
}

void menu_select_item(menu_t *menu, UINTN item)
{
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *conout = ST->ConOut;
  CHAR16 *sp;
  UINTN width = menu->width - 2;

  conout->SetCursorPosition(conout, menu->x + 1, menu->y + 1 + item);
  conout->SetAttribute(conout, EFI_BACKGROUND_BLUE);
  
  sp = menu->items[item];

  while(width--)
  {
    if(*sp != '\0')
      putchar(*sp++);
    else
      putchar(L' ');
  }

  conout->SetAttribute(conout, EFI_BACKGROUND_BLACK);
  menu->selected_item = item;

}

static void draw_menu(menu_t *menu)
{
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *conout = ST->ConOut;
  puts(L"Ant Boot\r\n"
       L"Created by Willian Oliveira\r\n");
  draw_box(menu->x, menu->y, menu->width, menu->heigth);
  
  UINTN i = 0;
  CHAR16 **spp;
  spp = menu->items;
  while(*spp++)
    menu_add_item(menu, i++);

  menu_select_item(menu, 0);
}

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *conout;

  init_lib(image_handle, system_table);

  conout = ST->ConOut;
  
  status = conout->SetMode(conout, 0);
  if(status)
    error(L"SetMode: Failed to set mode. ");
  
  UINTN columns;
  UINTN rows;
  status = conout->QueryMode(conout, 0, &columns, &rows);
  if(status)
    error(L"QueryMode: Failed to query mode.");

  CHAR16 *items[] =  {L"Item 1", L"Item 2", L"Item 3", NULL};

  menu_t menu = { 4, 4,
                  /*columns - 8*/ 20, /*rows - 8*/ 20,
                  items, 0xff
                };

  draw_menu(&menu);

  while(1);
  return 0;
}
