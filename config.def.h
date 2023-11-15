/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 15 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 2;    /* inner horizontal padding for statusbar */
static const int vertpadbar         = 8;    /* inner vertical padding for statustbar */
static const int tagoffset          = 0;
static const char *fonts[]          = {"Fira Code Nerd Font:style=Retina:size=18"};
static const char dmenufont[]       = "Fira Code Nerd Font:size=20:style:Regular";

/*  Theme */                          //"nord"
#include "colorthemes/rosepine_moon.h"


static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */

static const unsigned int baralpha = (0xff);
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] =     { fg_norm, bg_norm, border_norm },
	[SchemeSel]  =     { fg_sel,  bg_sel,  border_sel  },
	[SchemeTxt]  =     { fg_txt,  bg_txt,  border_txt  },
	[SchemeStatus]  =  { fg_st,   bg_st,   border_st   },
	[SchemeSystray]  = { fg_sys,  bg_sys,  border_sys  },
};

static const char *const autostart[] = {
	"/home/zac/Scripts/./sysinfo.sh", NULL,
	// "xrandr", "--output", "eDP-1", "--brightness", ".7", NULL,
    "setxkbmap", "-option", "caps:escape", NULL,
	"nm-applet", NULL,
	"picom", NULL,
    "nitrogen", "--restore", NULL,
    "pasystray", NULL,
    "blueman-applet", NULL,
    "conky", NULL,
    "asusctltray", NULL,
	NULL /* terminate */
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTxt]  =     { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]  =  { OPAQUE, baralpha, borderalpha },
	[SchemeSystray]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */

// static const char *tags[] = { "Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ", "Ⅵ", "Ⅶ", "Ⅷ", "Ⅸ" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
//static const char *tags[] = { "➀", "➁", "➂", "➃", "➄", "➅", "➆", "➇", "➈" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,     NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ "类",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{1, {{MODKEY, KEY}},                            view,           {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask, KEY}},                toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},                  tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *brightup[] = { "asusctl", "-n", NULL };
static const char *brightdown[] = { "asusctl", "-p", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL};
static const char *downvol[] = { "amixer", "-D", "pulse", "sset", "Master", "5%-", NULL };
static const char *email[] = { "thunderbird", NULL };
static const char *filebrowser[] = { "st", "-e", "ranger", NULL };
static const char *filebrowsergui[] = { "pcmanfm", NULL };
static const char *lockscr[] = { "slock", NULL };
static const char *mutevol[] = { "amixer", "-D", "pulse", "sset", "Master", "toggle", NULL };
static const char *neovim[] = { "st", "-e", "nvim", NULL };
static const char *octave_shell[] = { "st", "-e", "octave-cli", NULL };
static const char *poweroffcmd[] = {"poweroff", NULL };
static const char *rebootcmd[] = {"reboot", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *todolist[] = {"wezterm", "-e", "nvim", "/home/zac/.config/conky/todo.md", NULL};
// static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x25", NULL };
static const char *scratchpadcmd[] = { "alacritty", "-T", scratchpadname, NULL };
static const char *scrbrightdown[] = { "/home/zac/Scripts/./brightness.sh", "-", "eDP-1", NULL };
static const char *scrbrightup[] = { "/home/zac/Scripts/./brightness.sh", "+", "eDP-1", NULL };
static const char *screen_capture[] = { "scrot", NULL };
static const char *teams[] = { "teams", NULL };
// static const char *termcmd[] = { "alacritty", "-e", "tmux", "new", "-As0", NULL };
// static const char *termcmd[] = { "wezterm", NULL };
static const char *termcmd[] = { "wezterm", NULL };
static const char *upvol[] = { "amixer", "-D", "pulse", "sset", "Master", "5%+", NULL };
static const char *virtualbox[] = { "virtualbox", NULL };
static const char *web_browser[] = { "brave", NULL };
static const char *cycle_profiles[] = { "/home/zac/.config/sxhkd/scripts/cycle_profiles.sh", NULL };
static const char *toggle_fan_curve[] = { "/home/zac/.config/sxhkd/scripts/toggle_fan_curve.sh", NULL };

static const Keychord keychords[] = {
	/* modifier                     key        function        argument */
	{1, {{MODKEY, XK_Return}},                       spawn,          {.v = termcmd } },
	{1, {{MODKEY|ControlMask, XK_Return}},             togglescratch,  {.v = scratchpadcmd } },
	{1, {{MODKEY|ShiftMask, XK_Return}},             spawn,  {.v = todolist } },
    /* Launch applications */
	{1, {{MODKEY, XK_space}},                        spawn,          {.v = dmenucmd } },
	{1, {{MODKEY|ShiftMask, XK_f}},                  spawn,          {.v = filebrowser } },
	{1, {{MODKEY|ControlMask, XK_f}},                spawn,          {.v = filebrowsergui } },
	{1, {{MODKEY|ShiftMask, XK_e}},                  spawn,          {.v = email } },
	{1, {{MODKEY|ShiftMask, XK_b}},                  spawn,          {.v = web_browser } },
	{1, {{MODKEY|ShiftMask, XK_o}},                  spawn,          {.v = octave_shell } },
	{1, {{MODKEY|ShiftMask, XK_t}},                  spawn,          {.v = teams } },
	{1, {{MODKEY|ShiftMask, XK_v}},                  spawn,          {.v = virtualbox } },
	{1, {{MODKEY|ShiftMask, XK_n}},                  spawn,          {.v = neovim } },
    /* other stuff */
	{1, {{MODKEY|ShiftMask, XK_p}},                  spawn,          {.v = screen_capture } },
	{1, {{0, XF86XK_AudioRaiseVolume}},              spawn,          {.v = upvol } },
	{1, {{0, XF86XK_AudioLowerVolume}},              spawn,          {.v = downvol } },
	{1, {{0, XF86XK_AudioMute}},                     spawn,          {.v = mutevol } },
	{1, {{0, XF86XK_KbdBrightnessUp}},               spawn,          {.v = brightup } },
	{1, {{0, XF86XK_KbdBrightnessDown}},             spawn,          {.v = brightdown } },
	{1, {{0, XF86XK_MonBrightnessUp}},               spawn,          {.v = scrbrightup } },
	{1, {{0, XF86XK_MonBrightnessDown}},             spawn,          {.v = scrbrightdown } },
	{1, {{MODKEY|ShiftMask|ControlMask, XK_r}},      spawn,          {.v = rebootcmd } },
	{1, {{MODKEY|ShiftMask|ControlMask, XK_q}},      spawn,          {.v = poweroffcmd } },
	{1, {{MODKEY|ShiftMask|ControlMask, XK_l}},      spawn,          {.v = lockscr } },
	{1, {{0, XF86XK_Launch1}},                       spawn,          {.v = cycle_profiles } },
	{1, {{0, XF86XK_Launch4}},                       spawn,          {.v = toggle_fan_curve } },
	{1, {{MODKEY, XK_b}},                            togglebar,      {0} },
	{1, {{MODKEY, XK_j}},                            focusstack,     {.i = +1 } },
	{1, {{MODKEY, XK_k}},                            focusstack,     {.i = -1 } },
	{1, {{MODKEY, XK_i}},                            incnmaster,     {.i = +1 } },
	{1, {{MODKEY, XK_d}},                            incnmaster,     {.i = -1 } },
	{1, {{MODKEY, XK_h}},                            setmfact,       {.f = -0.05} },
	{1, {{MODKEY, XK_l}},                            setmfact,       {.f = +0.05} },
	{1, {{MODKEY|ShiftMask, XK_j}},                  rotatestack,    {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_k}},                  rotatestack,    {.i = -1 } },
	{1, {{MODKEY|ControlMask, XK_j}},                movestack,      {.i = +1 } },
	{1, {{MODKEY|ControlMask, XK_k}},                movestack,      {.i = -1 } },
	{1, {{MODKEY|ShiftMask|ControlMask, XK_Return}}, zoom,           {0} },
	{1, {{MODKEY, XK_Tab}},                          view,           {0} },
	{1, {{MODKEY|ShiftMask, XK_c}},                  killclient,     {0} },
	{1, {{MODKEY|ShiftMask, XK_x}},                  killunsel,      {0} },
	{1, {{MODKEY, XK_t}},                            setlayout,      {.v = &layouts[0]} },
	{1, {{MODKEY, XK_f}},                            setlayout,      {.v = &layouts[1]} },
	{1, {{MODKEY, XK_m}},                            setlayout,      {.v = &layouts[2]} },
	{1, {{MODKEY|ControlMask, XK_space}},            setlayout,      {0} },
	{1, {{MODKEY|ShiftMask, XK_space}},              togglefloating, {0} },
	{1, {{MODKEY, XK_Down}},                         moveresize,     {.v = "0x 25y 0w 0h" } },
	{1, {{MODKEY, XK_Up}},                           moveresize,     {.v = "0x -25y 0w 0h" } },
	{1, {{MODKEY, XK_Right}},                        moveresize,     {.v = "25x 0y 0w 0h" } },
	{1, {{MODKEY, XK_Left}},                         moveresize,     {.v = "-25x 0y 0w 0h" } },
	{1, {{MODKEY|ShiftMask, XK_Down}},               moveresize,     {.v = "0x 0y 0w 25h" } },
	{1, {{MODKEY|ShiftMask, XK_Up}},                 moveresize,     {.v = "0x 0y 0w -25h" } },
	{1, {{MODKEY|ShiftMask, XK_Right}},              moveresize,     {.v = "0x 0y 25w 0h" } },
	{1, {{MODKEY|ShiftMask, XK_Left}},               moveresize,     {.v = "0x 0y -25w 0h" } },
	{1, {{MODKEY|ControlMask, XK_Up}},               moveresizeedge, {.v = "t"} },
	{1, {{MODKEY|ControlMask, XK_Down}},             moveresizeedge, {.v = "b"} },
	{1, {{MODKEY|ControlMask, XK_Left}},             moveresizeedge, {.v = "l"} },
	{1, {{MODKEY|ControlMask, XK_Right}},            moveresizeedge, {.v = "r"} },
	{1, {{MODKEY|ControlMask|ShiftMask, XK_Up}},     moveresizeedge, {.v = "T"} },
	{1, {{MODKEY|ControlMask|ShiftMask, XK_Down}},   moveresizeedge, {.v = "B"} },
	{1, {{MODKEY|ControlMask|ShiftMask, XK_Left}},   moveresizeedge, {.v = "L"} },
	{1, {{MODKEY|ControlMask|ShiftMask, XK_Right}},  moveresizeedge, {.v = "R"} },
	{1, {{MODKEY, XK_0}},                            view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask, XK_0}},                  tag,            {.ui = ~0 } },
	{1, {{MODKEY, XK_comma}},                        focusmon,       {.i = -1 } },
	{1, {{MODKEY, XK_period}},                       focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_comma}},              tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask, XK_period}},             tagmon,         {.i = +1 } },
	{1, {{MODKEY, XK_minus}},                        setgaps,        {.i = -5 } },
	{1, {{MODKEY, XK_plus}},                         setgaps,        {.i = +5 } },
	{1, {{MODKEY|ShiftMask, XK_minus}},              setgaps,        {.i = GAP_RESET } },
	{1, {{MODKEY|ShiftMask, XK_plus}},               setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{1, {{MODKEY|ShiftMask, XK_q}},                   quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
