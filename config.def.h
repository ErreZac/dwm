/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps[]    = { 25 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 25 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"Victor Mono Nerd Font:style=Medium:size=20"};
static const char dmenufont[]       = "Victor Mono Nerd Font:size=20:style:Regular";

/*  Theme */                          //"nord"
static const char fg_norm[]     = "#fbf1c7";//"#C3BAC6"; // D9E0EE"#fabd2f"; // "#D8DEE9";
static const char bg_norm[]     = "#282828";//"#1E1E2E"; // "#282828"; // "#2E3440";
static const char border_norm[] = "#928374";//"#575268"; // "#282828"; // "#3B4252";
static const char fg_sel[]      = "#fbf1c7";//"#D9E0EE"; //C9CBFF "#1d2021"; // "#ECEFF4";
static const char bg_sel[]      = "#458588";//"#575268"; // C9CBFF"#fabd2f"; // "#434C5E";
static const char border_sel[]  = "#458588";//"#D9E0EE"; //C9CBFF "#fabd2f"; // "#88C0D0";

static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 25;       /* horizontal padding of bar */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg_norm, bg_norm, border_norm },
	[SchemeSel]  = { fg_sel,  bg_sel,  border_sel  },
};

/* tagging */

static const char *tags[] = { "Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ", "Ⅵ", "Ⅶ", "Ⅷ", "Ⅸ" };
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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "🗗",      NULL },    /* no layout function means floating behavior */
	{ "类",      monocle },
	{ "",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL};//, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *todolist[] = { "st", "-e", "vim", "/home/zac/Documents/to_do_list.md", NULL };
static const char *termtabcmd[] = { "tabbed", "-c", "-r", "2", "st", "-w", "''", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x25", NULL };
static const char *filebrowser[] = { "st", "-e", "ranger", NULL };
static const char *email[] = { "thunderbird", NULL };
static const char *web_browser[] = { "brave-browser", NULL };
static const char *octave_shell[] = { "st", "-e", "octave-cli", NULL };
static const char *teams[] = { "teams", NULL };
static const char *virtualbox[] = { "primusrun", "virtualbox", NULL };
static const char *screen_capture[] = { "scrot", NULL };
static const char *upvol[] = { "amixer", "-D", "pulse", "sset", "Master", "5%+", NULL };
static const char *downvol[] = { "amixer", "-D", "pulse", "sset", "Master", "5%-", NULL };
static const char *mutevol[] = { "amixer", "-D", "pulse", "sset", "Master", "toggle", NULL };
static const char *brightup[] = { "asusctl", "-n", NULL };
static const char *brightdown[] = { "asusctl", "-p", NULL };
static const char *scrbrightup[] = { "/home/zac/Documents/scripts/./brightness.sh", "+", "eDP", NULL };
static const char *scrbrightdown[] = { "/home/zac/Documents/scripts/./brightness.sh", "-", "eDP", NULL };
static const char *poweroffcmd[] = { "sudo", "poweroff", NULL };
static const char *rebootcmd[] = { "sudo", "reboot", NULL };
static const char *lockscr[] = { "slock", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = todolist } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = termtabcmd } },
	{ MODKEY|ShiftMask,             XK_Return, togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filebrowser } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = email } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = web_browser } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = octave_shell } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = teams } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = virtualbox } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = screen_capture } },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          {.v = upvol } },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          {.v = downvol } },
	{ 0, XF86XK_AudioMute,                     spawn,          {.v = mutevol } },
	{ 0, XF86XK_KbdBrightnessUp,               spawn,          {.v = brightup } },
	{ 0, XF86XK_KbdBrightnessDown,             spawn,          {.v = brightdown } },
	{ 0, XF86XK_MonBrightnessUp,           spawn,          {.v = scrbrightup } },
	{ 0, XF86XK_MonBrightnessDown,         spawn,          {.v = scrbrightdown } },
	{ MODKEY|ShiftMask|ControlMask, XK_r,      spawn,          {.v = rebootcmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_q,      spawn,          {.v = poweroffcmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_l,      spawn,          {.v = lockscr } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_x,      killunsel,      {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_plus,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_plus,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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
