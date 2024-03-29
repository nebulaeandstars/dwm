/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 6;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

static const char *fonts[] = {
    "monospace:size=12",
    "ionicons:pixelsize=12:antialias=true:autohint=true",
    "Nerd Font Complete:pixelsize=12:antialias=true:autohint=true",
    "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true",
    "JoyPixels:pixelsize=12:antialias=true:autohint=true"
};
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#2d2d2d";
static const char col_gray2[]       = "#4f4f4f";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#2d2d2d";
static const char col_cyan[]        = "#b4eded";
static const unsigned int baralpha = 0x75;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border     */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "HHH",      grid },
    { "###",      nrowgrid },
    { "---",      horizgrid },
    { ":::",      gaplessgrid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "><>",      NULL },    /* no layout function means floating behavior */
    { NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *layoutmenu_cmd = "layoutmenu";
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"
static Key keys[] = {
    /* modifier                     key        function        argument */

    // windows
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY|ControlMask,           XK_j,      rotatestack,    {.i = +1 } },
    { MODKEY|ControlMask,           XK_k,      rotatestack,    {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_j,      incnmaster,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_k,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_space,  zoom,           {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },

    // gaps
    { MODKEY,                          XK_g,      togglegaps,     {0} },
    { MODKEY|ShiftMask,                XK_g,      defaultgaps,    {0} },
    { MODKEY|ShiftMask,                XK_l,      incrgaps,       {.i = +1 } },
    { MODKEY|ShiftMask,                XK_h,      incrgaps,       {.i = -1 } },
    /* { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } }, */

    { MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY|ControlMask,           XK_s,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ControlMask,           XK_d,      setlayout,      {.v = &layouts[3]} },
    { MODKEY|ControlMask,           XK_g,      setlayout,      {.v = &layouts[8]} },
    { MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[11]} },
    { MODKEY|ControlMask|ShiftMask, XK_m,      setlayout,      {.v = &layouts[12]} },
    { MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[13]} },
    { MODKEY|ControlMask,           XK_space,  setlayout,      {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },

    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
    { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
