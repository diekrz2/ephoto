#ifndef _EPHOTO_H_
# define _EPHOTO_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <Eet.h>
# include <Ecore.h>
# include <Ecore_Evas.h>
# include <Ecore_Ipc.h>
# include <Ecore_File.h>
# include <Efreet_Mime.h>
# include <Elementary.h>
# include <Elementary_Cursor.h>
# include <Eina.h>
# include <Edje.h>
# include <Evas.h>
# include <Eio.h>

# include "config.h"

#if HAVE_GETTEXT
# include <locale.h>
# include <libintl.h>
# define _(string)                       gettext(string)
#else
# define _(string)                       (string)
# define ngettext(String1, String2, Var) Var == 1 ? String1 : String2
#endif

# define USE_IPC

/*local types*/
typedef struct _Ephoto_Config             Ephoto_Config;
typedef struct _Ephoto                    Ephoto;
typedef struct _Ephoto_Entry              Ephoto_Entry;
typedef struct _Ephoto_Event_Entry_Create Ephoto_Event_Entry_Create;

typedef enum _Ephoto_State                Ephoto_State;
typedef enum _Ephoto_Orient               Ephoto_Orient;
typedef enum _Ephoto_Sort                 Ephoto_Sort;
typedef enum _Ephoto_Ipc_Domain           Ephoto_Ipc_Domain;

/*main window functions*/
Evas_Object *ephoto_window_add(const char *path);
void         ephoto_title_set(Ephoto *ephoto, const char *title);
void         ephoto_thumb_size_set(Ephoto *ephoto, int size);
Evas_Object *ephoto_thumb_add(Ephoto *ephoto, Evas_Object *parent,
                              Ephoto_Entry *entry);
void         ephoto_directory_set(Ephoto *ephoto, const char *path,
                                  Elm_Object_Item *expanded, Eina_Bool dirs_only,
                                  Eina_Bool thumbs_only);
void         ephoto_show_folders(Ephoto *ephoto, Eina_Bool toggle);

/*config panel functions*/
Eina_Bool                  ephoto_config_init(Ephoto *em);
void                       ephoto_config_save(Ephoto *em);
void                       ephoto_config_free(Ephoto *em);
void                       ephoto_config_main(Ephoto *em);

/*single image functions*/
Evas_Object *ephoto_single_browser_add(Ephoto *ephoto, Evas_Object *parent);
void         ephoto_single_browser_show_controls(Ephoto *ephoto);
void         ephoto_single_browser_entries_set(Evas_Object *obj, Eina_List *entries);
void         ephoto_single_browser_entry_set(Evas_Object *obj, Ephoto_Entry *entry);
void         ephoto_single_browser_focus_set(Ephoto *ephoto);
void         ephoto_single_browser_path_pending_set(Evas_Object *obj,
                                                    const char *path);
void         ephoto_single_browser_path_pending_unset(Evas_Object *obj);
void         ephoto_single_browser_path_created(Evas_Object *obj, Ephoto_Entry *entry);
void         ephoto_single_browser_image_data_update(Evas_Object *main,
                                                     Evas_Object *image,
                                                     unsigned int *image_data,
                                                     Evas_Coord w,
                                                     Evas_Coord h);
void         ephoto_single_browser_image_data_done(Evas_Object *main,
                                                   unsigned int *image_data,
                                                   Evas_Coord w,
                                                   Evas_Coord h);
void         ephoto_single_browser_cancel_editing(Evas_Object *main);
void         ephoto_single_browser_slideshow(Evas_Object *obj);
/* smart callbacks called: "back" - the user wants to go back to the previous
 * screen. */

/*slideshow functions*/
Evas_Object *ephoto_slideshow_add(Ephoto *ephoto, Evas_Object *parent);
void         ephoto_slideshow_entries_set(Evas_Object *obj, Eina_List *entries);
void         ephoto_slideshow_entry_set(Evas_Object *obj, Ephoto_Entry *entry);
void         ephoto_slideshow_show_controls(Ephoto *ephoto);
/* smart callbacks called: "back" - the user wants to go back to the previous
 * screen. */

/*thumbnail browser functions*/
Evas_Object *ephoto_thumb_browser_add(Ephoto *ephoto, Evas_Object *parent);
void         ephoto_thumb_browser_show_controls(Ephoto *ephoto);
void         ephoto_thumb_browser_insert(Ephoto *ephoto, Ephoto_Entry *entry);
void         ephoto_thumb_browser_remove(Ephoto *ephoto, Ephoto_Entry *entry);
void         ephoto_thumb_browser_update(Ephoto *ephoto, Ephoto_Entry *entry);
void         ephoto_thumb_browser_update_info_label(Ephoto *ephoto);
void         ephoto_thumb_browser_slideshow(Evas_Object *obj);
void         ephoto_thumb_browser_paste(Ephoto *ephoto, Elm_Object_Item *item);
void         ephoto_thumb_browser_clear(Ephoto *ephoto);
void         ephoto_thumb_browser_recalc(Ephoto *ephoto);
void         ephoto_thumb_browser_dirs_only_set(Ephoto *ephoto, Eina_Bool dirs_only);
/* smart callbacks called: "selected" - an item in the thumb browser is
 * selected. The selected Ephoto_Entry is passed as event_info argument. */

/*directory browser functions*/
Evas_Object *ephoto_directory_browser_add(Ephoto *ephoto, Evas_Object *parent);
void         ephoto_directory_browser_initialize_structure(Ephoto *ephoto, char *rp);
void         ephoto_directory_browser_top_dir_set(Ephoto *ephoto, const char *dir);
void         ephoto_directory_browser_clear(Ephoto *ephoto);

/*thumbnailing functions taken from enlightenment*/
int          e_thumb_init(void);
int          e_thumb_shutdown(void);
Evas_Object *e_thumb_icon_add(Evas *evas, Eina_Bool aspect);
void         e_thumb_icon_file_set(Evas_Object *obj, const char *file, const char *key);
void         e_thumb_icon_size_set(Evas_Object *obj, Evas_Coord w, Evas_Coord h);
void         e_thumb_icon_begin(Evas_Object *obj);
void         e_thumb_icon_end(Evas_Object *obj);
void         e_thumb_icon_rethumb(Evas_Object *obj);
const char  *e_thumb_sort_id_get(Evas_Object *obj);
void         e_thumb_client_data(Ecore_Ipc_Event_Client_Data *e);
void         e_thumb_client_del(Ecore_Ipc_Event_Client_Del *e);
int          e_ipc_init(void);
int          e_ipc_shutdown(void);

/*editing functions*/
Evas_Object *ephoto_editor_add(Ephoto *ephoto, Evas_Object *parent, const char *title,
                               const char *data_name, void *data);
void         ephoto_editor_del(Evas_Object *obj, Evas_Object *parent);
void         ephoto_cropper_add(Ephoto *ephoto, Evas_Object *main, Evas_Object *parent,
                                Evas_Object *image_parent, Evas_Object *image);
void         ephoto_bcg_add(Ephoto *ephoto, Evas_Object *main, Evas_Object *parent,
                            Evas_Object *image);
void         ephoto_hsv_add(Ephoto *ephoto, Evas_Object *main, Evas_Object *parent,
                            Evas_Object *image);
void         ephoto_color_add(Ephoto *ephoto, Evas_Object *main, Evas_Object *parent,
                              Evas_Object *image);
void         ephoto_red_eye_add(Ephoto *ephoto, Evas_Object *main, Evas_Object *parent,
                                Evas_Object *image);
void         ephoto_scale_add(Ephoto *ephoto, Evas_Object *main, Evas_Object *parent,
                              Evas_Object *image, const char *file);
void         ephoto_filter_blur(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_sharpen(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_dither(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_black_and_white(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_old_photo(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_painting(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_posterize(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_sketch(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_invert(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_edge(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_emboss(Ephoto *ephoto, Evas_Object *image);
void         ephoto_filter_histogram_eq(Ephoto *ephoto, Evas_Object *image);

/*file functions*/
#ifdef HAVE_LIBEXIF
Eina_Bool    ephoto_file_has_exif(const char *file);
Eina_List   *ephoto_file_get_exif_data(const char *file);
void         ephoto_file_exif_data(Ephoto *ephoto, const char *file);
#endif
void         ephoto_file_save_image(Ephoto *ephoto, Ephoto_Entry *entry,
                                    Evas_Object *image);
void         ephoto_file_save_image_as(Ephoto *ephoto, Ephoto_Entry *entry,
                                       Evas_Object *image);
void         ephoto_file_upload_image(Ephoto *ephoto, Ephoto_Entry *entry);
void         ephoto_file_new_dir(Ephoto *ephoto, const char *path);
void         ephoto_file_rename(Ephoto *ephoto, const char *path);
void         ephoto_file_move(Ephoto *ephoto, Eina_List *files, const char *path);
void         ephoto_file_copy(Ephoto *ephoto, Eina_List *files, const char *path);
void         ephoto_file_paste(Ephoto *ephoto, Eina_List *files, Eina_Bool copy,
                               const char *path);
void         ephoto_file_delete(Ephoto *ephoto, Eina_List *files,
                                Eina_File_Type type);
void         ephoto_file_empty_trash(Ephoto *ephoto, Eina_List *files);

/*data types and structures*/

enum _Ephoto_State
{
   EPHOTO_STATE_THUMB,
   EPHOTO_STATE_SINGLE,
   EPHOTO_STATE_SLIDESHOW
};

enum _Ephoto_Orient
{
   EPHOTO_ORIENT_0 = 1,
   EPHOTO_ORIENT_FLIP_HORIZ = 2,
   EPHOTO_ORIENT_180 = 3,
   EPHOTO_ORIENT_FLIP_VERT = 4,
   EPHOTO_ORIENT_FLIP_VERT_90 = 5,
   EPHOTO_ORIENT_90 = 6,
   EPHOTO_ORIENT_FLIP_HORIZ_90 = 7,
   EPHOTO_ORIENT_270 = 8
};

enum _Ephoto_Sort
{
   EPHOTO_SORT_ALPHABETICAL_ASCENDING,
   EPHOTO_SORT_ALPHABETICAL_DESCENDING,
   EPHOTO_SORT_MODTIME_ASCENDING,
   EPHOTO_SORT_MODTIME_DESCENDING,
   EPHOTO_SORT_SIMILARITY
};

enum _Ephoto_Ipc_Domain
{
   EPHOTO_IPC_DOMAIN_THUMB
};

struct _Ephoto_Config
{
   int          config_version;
   int          thumb_size;
   int          thumb_gen_size;
   int          window_width;
   int          window_height;
   double       slideshow_timeout;
   double       left_size;
   double       right_size;
   const char  *directory;
   const char  *slideshow_transition;
   const char  *open;
   Eina_Bool    fsel_hide;
   Eina_Bool    prompts;
   Eina_Bool    drop;
   Eina_Bool    movess;
   Eina_Bool    smooth;
   Eina_Bool    firstrun;
   Eina_Bool    folders;
   Eina_Bool    thumbnail_aspect;
   Evas_Object *slide_time;
   Evas_Object *slide_trans;
   Evas_Object *open_dir;
   Evas_Object *open_dir_custom;
   Evas_Object *show_prompts;
   Evas_Object *move_drop;
   Evas_Object *smooth_scale;
   Evas_Object *slide_move;
   Evas_Object *show_folders;
   Evas_Object *thumb_aspect;
   Evas_Object *panel_size;
};

struct _Ephoto
{
   Evas_Object               *win;
   Evas_Object               *main;
   Evas_Object               *layout;
   Evas_Object               *pager;
   Evas_Object               *statusbar;
   Evas_Object               *folders_button;
   Evas_Object               *folders_icon;
   Evas_Object               *view_button;
   Evas_Object               *controls_left;
   Evas_Object               *controls_right;
   Evas_Object               *infolabel;
   Evas_Object               *exit;

   Evas_Object               *thumb_browser;
   Evas_Object               *single_browser;
   Evas_Object               *slideshow;
   Evas_Object               *dir_browser;
   Evas_Object               *file_popup;

   Eina_Bool                  folders_toggle;
   Eina_Bool                  thumb_browser_dirty;
   Eina_List                 *entries;
   Eina_List                 *selentries;
   Eina_List                 *searchentries;
   Eina_List                 *thumbs;

   Eio_Monitor               *monitor;
   Eina_List                 *monitor_handlers;
   Eina_List                 *file_pos;
   Eina_List                 *upload_handlers;
   Ecore_Thread              *file_thread;
   Ecore_Con_Url             *url_up;
   char                      *url_ret;
   char                      *upload_error;
   int                        file_errors;
   int                        entry_free;

   const char                *top_directory;
   const char                *config_path;
   const char                *trash_path;
   const char                *destination;

   int                        thumb_gen_size;

   struct
   {
      Ecore_Timer            *thumb_regen;
   } timer;
   struct
   {
      Ecore_Job              *change_dir;
   } job;

   Eio_File                  *ls;

   Evas_Object               *prefs_win;
   Ephoto_State               state, prev_state;

   Ephoto_Config             *config;
   Ephoto_Sort                sort;
   /* if launched via menu or with no path org_open is NULL
         otherwise stores ephoto->config->open value to restore at exit.*/
   const char                *org_open; 
};

struct _Ephoto_Entry
{
   const char      *path;
   const char      *basename;
   const char      *label;
   const char      *sort_id;
   double           size;
   Ephoto          *ephoto;
   Eio_Monitor     *monitor;
   Eina_List       *monitor_handlers;
   Elm_Object_Item *item;
   Elm_Object_Item *parent;
   Eina_List       *free_listeners;
   Eina_Bool        is_dir;
   Eina_Bool        is_link;
   Eina_Bool        no_delete;
   Evas_Object     *genlist;
   Evas_Object     *gengrid;
   Evas_Object     *thumb;
};

struct _Ephoto_Event_Entry_Create
{
   Ephoto_Entry *entry;
};

/*ephoto file functions*/
Ephoto_Entry *ephoto_entry_new(Ephoto *ephoto, const char *path,
                               const char *label, Eina_File_Type type);
Eina_Bool     ephoto_entry_exists(Ephoto *ephoto, const char *path);
void          ephoto_entry_free(Ephoto *ephoto, Ephoto_Entry *entry);
void          ephoto_entry_free_listener_add(Ephoto_Entry *entry,
                                             void (*cb)(void *data,
                                             const Ephoto_Entry *entry),
                                             const void *data);
void          ephoto_entry_free_listener_del(Ephoto_Entry *entry,
                                             void (*cb)(void *data,
                                             const Ephoto_Entry *entry),
                                             const void *data);
void          ephoto_entries_free(Ephoto *ephoto);
int           ephoto_entries_cmp(const void *pa, const void *pb);

/*check if image can be loaded*/
static inline Eina_Bool
_ephoto_eina_file_direct_info_image_useful(const Eina_File_Direct_Info *info)
{
   const char *type, *bname;
   int i = 0, count = 0;

   const char *filters[] = {
      "png", "jpeg", "jpg", "eet", "xpm", "tiff", "gif", "svg", "webp",
      "pmaps", "bmp", "tga", "wbmp", "ico", "psd", "jp2k", "generic", "3fr",
      "ari", "arw", "bay", "crw", "cr2", "cap", "dcs", "dcr", "dng", "drf",
      "eip", "erf", "fff", "iiq", "k25", "kdc", "mdc", "mef", "mos", "mrw",
      "nef", "nrw", "obm", "orf", "pef", "ptx", "pxn", "r3d", "raf", "raw",
      "rwl", "rw2", "rwz", "sr2", "srf", "srw", "tif", "x3f", "avif", "heif", "jxl"
   };

   bname = info->path + info->name_start;
   if (bname[0] == '.')
     return EINA_FALSE;
   if ((info->type != EINA_FILE_REG) && (info->type != EINA_FILE_UNKNOWN) &&
       (info->type != EINA_FILE_LNK))
     return EINA_FALSE;

   type = strrchr(bname, '.');
   if (!type)
     return EINA_FALSE;
   count = sizeof(filters) / sizeof(filters[0]);

   for (i = 0; i < count; i++)
     {
        if (!strcasecmp(type + 1, filters[i]))
          return evas_object_image_extension_can_load_get(bname);
     }
   return EINA_FALSE;
}

/*check if image can be saved*/
static inline Eina_Bool
_ephoto_file_image_can_save(const char *ext)
{
   int i = 0, count = 0;

   const char *filters[] = {
      "png", "jpeg", "jpg", "eet", "xpm", "tiff", "tif", "gif", "svg", "webp",
      "pmaps", "bmp", "wbmp", "avif", "jxl", "heif", "ico", "generic"
   };
   count = sizeof(filters) / sizeof(filters[0]);
   for (i = 0; i < count; i++)
     {
        if (!strcasecmp(ext, filters[i]))
          return EINA_TRUE;
     }
   return EINA_FALSE;
}

/*RGBA Functions*/
static inline int
ephoto_normalize_color(int color)
{
   return (color >= 0 && color <= 255) ? color : (color < 0) ? 0 : 255;
}

static inline int
ephoto_mul_color_alpha(int color, int alpha)
{
   return (alpha > 0 && alpha <= 255) ? (color * (255 / alpha)) : color;
}

static inline int
ephoto_demul_color_alpha(int color, int alpha)
{
   return (alpha > 0 && alpha <= 255) ? ((color * alpha) / 255) : color;
}

/*event types*/
extern int EPHOTO_EVENT_ENTRY_CREATE;
extern int EPHOTO_EVENT_POPULATE_START;
extern int EPHOTO_EVENT_POPULATE_END;
extern int EPHOTO_EVENT_POPULATE_ERROR;
extern int EPHOTO_EVENT_EDITOR_RESET;
extern int EPHOTO_EVENT_EDITOR_APPLY;
extern int EPHOTO_EVENT_EDITOR_CANCEL;
extern int EPHOTO_EVENT_EDITOR_BACK;

#define CRIT(...)        EINA_LOG_CRIT(__VA_ARGS__)
#define ERR(...)         EINA_LOG_ERR(__VA_ARGS__)
#define WRN(...)         EINA_LOG_WARN(__VA_ARGS__)
#define INF(...)         EINA_LOG_INFO(__VA_ARGS__)
#define DBG(...)         EINA_LOG_DBG(__VA_ARGS__)
#define EPHOTO_WEIGHT evas_object_size_hint_weight_set
#define EPHOTO_ALIGN  evas_object_size_hint_align_set
#define EPHOTO_EXPAND(X) EPHOTO_WEIGHT((X), EVAS_HINT_EXPAND, EVAS_HINT_EXPAND)
#define EPHOTO_FILL(X)   EPHOTO_ALIGN((X), EVAS_HINT_FILL, EVAS_HINT_FILL)

#endif
