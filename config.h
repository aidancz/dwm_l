/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "google-chrome-stable"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 0;       /* horiz inner gap between windows */
static unsigned int gappiv    = 0;       /* vert inner gap between windows */
static unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 0;        /* 0 means bottom bar */
static char fonts_0[]            = "monospace:size=15";
static char fonts_1[]            = "monospace:size=15";
static char fonts_2[]            = "monospace:size=15";
static char *fonts[]          = { fonts_0, fonts_1, fonts_2 };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class	instance	title			tags mask	isfloating	isterminal	noswallow	monitor */
	{ "Gimp",	NULL,		NULL,			1 << 8,	0,		0,		0,		-1 },
	{ TERMCLASS,	NULL,		NULL,			0,		0,		1,		0,		-1 },
	{ TERMCLASS,	"bg",		NULL,			1 << 7,	0,		1,		0,		-1 },
	{ TERMCLASS,	"spterm",	NULL,			SPTAG(0),	1,		1,		0,		-1 },
	{ TERMCLASS,	"spcalc",	NULL,			SPTAG(1),	1,		1,		0,		-1 },
	{ NULL,	NULL,		"Event Tester",	0,		0,		0,		1,		-1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEYC MODKEY|ControlMask
#define MODKEYA MODKEY|Mod1Mask
#define MODKEYS MODKEY|ShiftMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY,		view,		{.ui = 1 << TAG} }, \
	{ MODKEYA,			KEY,		toggleview,	{.ui = 1 << TAG} }, \
	{ MODKEYC,			KEY,		tag,		{.ui = 1 << TAG} }, \
	{ MODKEYS,			KEY,		toggletag,	{.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,	XK_m,	ACTION##stack,	{.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",		STRING,	&fonts_0 },
		{ "fonta",		STRING,	&fonts_1 },
		{ "fontb",		STRING,	&fonts_2 },
		{ "normbgcolor",	STRING,	&normbgcolor },
		{ "normfgcolor",	STRING,	&normfgcolor },
		{ "selbgcolor",		STRING,	&selbgcolor },
		{ "selfgcolor",		STRING,	&selfgcolor },
		{ "normbordercolor",	STRING,	&normbordercolor },
		{ "selbordercolor",	STRING,	&selbordercolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
//	modifier			key			function	argument
	{ MODKEYC,			XK_q,			spawn,		{.v = (const char*[]){ "sysact", NULL } } },

	{ MODKEY,			XK_Left,		focusmon,	{.i = -1 } },
	{ MODKEYC,			XK_Left,		tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,		focusmon,	{.i = +1 } },
	{ MODKEYC,			XK_Right,		tagmon,		{.i = +1 } },

	STACKKEYS(MODKEY,					focus)
	STACKKEYS(MODKEYC,					push)
//	<c-j,k,m> are automatically bound above in STACKKEYS
	TAGKEYS(			XK_1,			0)
	TAGKEYS(			XK_2,			1)
	TAGKEYS(			XK_3,			2)
	TAGKEYS(			XK_4,			3)
	TAGKEYS(			XK_5,			4)
	TAGKEYS(			XK_6,			5)
	TAGKEYS(			XK_7,			6)
	TAGKEYS(			XK_8,			7)
	TAGKEYS(			XK_9,			8)
	{ MODKEY,			XK_0,			view,		{.ui = ~0 } },
	{ MODKEYC,			XK_0,			tag,		{.ui = ~0 } },
	{ MODKEY,			XK_h,			shiftview,	{ .i = -1 } },
	{ MODKEYC,			XK_h,			shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_l,			shiftview,	{ .i = 1 } },
	{ MODKEYC,			XK_l,			shifttag,	{ .i = 1 } },
	{ MODKEY,			XK_o,			view,		{0} }, // view previous tag

	{ MODKEY,			XK_f,			setlayout,	{.v = &layouts[0]} }, // tile
	{ MODKEYC,			XK_f,			setlayout,	{.v = &layouts[1]} }, // tile_master on top
	{ MODKEY,			XK_VoidSymbol,		setlayout,	{.v = &layouts[2]} }, // fibonacci
	{ MODKEY,			XK_VoidSymbol,		setlayout,	{.v = &layouts[3]} }, // dwindle
	{ MODKEY,			XK_d,			setlayout,	{.v = &layouts[4]} }, // monocle_master on left
	{ MODKEYC,			XK_d,			setlayout,	{.v = &layouts[5]} }, // monocle
	{ MODKEY,			XK_VoidSymbol,		setlayout,	{.v = &layouts[6]} }, // centermaster
	{ MODKEYC,			XK_VoidSymbol,		setlayout,	{.v = &layouts[7]} }, // centermaster_master float
	{ MODKEY,			XK_VoidSymbol,		setlayout,	{.v = &layouts[8]} }, // float (aka normie)
	{ MODKEYS,			XK_k,			incnmaster,	{.i = +1 } },
	{ MODKEYS,			XK_j,			incnmaster,	{.i = -1 } },
	{ MODKEYS,			XK_h,			setmfact,	{.f = -0.05} },
	{ MODKEYS,			XK_l,			setmfact,	{.f = +0.05} },
	{ MODKEY,			XK_VoidSymbol,		togglebar,	{0} },
	{ MODKEY,			XK_VoidSymbol,		togglegaps,	{0} },
	{ MODKEY,			XK_VoidSymbol,		togglesmartgaps,{0} },
	{ MODKEY,			XK_VoidSymbol,		incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_VoidSymbol,		incrgaps,	{.i = -3 } },
	{ MODKEY,			XK_VoidSymbol,		defaultgaps,	{0} },

	{ MODKEY,			XK_q,			killclient,	{0} }, // window close
	{ MODKEY,			XK_n,			zoom,		{0} }, // window first (if already first, move second window to first)
	{ MODKEY,			XK_Escape,		togglefloating,	{0} }, // window float
	{ MODKEY,			XK_s,			togglesticky,	{0} }, // window sticky
	{ MODKEY,			XK_a,			togglefullscr,	{0} }, // window full screen

	{ MODKEY,			XK_Return,		spawn,		{.v = termcmd } },
	{ MODKEY,			XK_space,		togglescratch,	{.ui = 0} },
//	{ MODKEYA,			XK_Return,		togglescratch,	{.ui = 1} },
	{ MODKEY,			XK_e,			spawn,		{.v = (const char*[]){ "emacsclient", "-c", "-a", "", NULL } } },
// https://github.com/daviwil/emacs-from-scratch/blob/master/show-notes/Emacs-Tips-08.org#opening-files-from-the-command-line
//	{ MODKEYC,			XK_c,			spawn,		{.v = (const char*[]){ "nutstore", NULL } } },
//	{ MODKEY,			XK_c,			spawn,		{.v = (const char*[]){ TERMINAL, "-e", "profanity", NULL } } },
//	{ MODKEY,			XK_m,			spawn,		{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
//	{ MODKEY,			XK_n,			spawn,		{.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
//	{ MODKEY,			XK_i,			spawn,		{.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
//	{ MODKEY,			XK_r,			spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
//	{ MODKEYC,			XK_n,			spawn,		{.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	{ MODKEY,			XK_w,			spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,			XK_i,			spawn,		{.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEYC,			XK_i,			spawn,		{.v = (const char*[]){ "dmenuunicode", NULL } } },
	{ MODKEYC,			XK_p,			spawn,		{.v = (const char*[]){ "passmenu", NULL } } },
// ncmpcpp_music
//	{ MODKEY,			XK_p,			spawn,		{.v = (const char*[]){ "mpc", "toggle", NULL } } },
//	{ MODKEY,			XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
//	{ MODKEY,			XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
//	{ MODKEY,			XK_bracketright,	spawn,		{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
//	{ MODKEYS,			XK_bracketright,	spawn,		{.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
//	{ MODKEY,			XK_comma,		spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
//	{ MODKEYS,			XK_comma,		spawn,		{.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
//	{ MODKEY,			XK_period,		spawn,		{.v = (const char*[]){ "mpc", "next", NULL } } },
//	{ MODKEYS,			XK_period,		spawn,		{.v = (const char*[]){ "mpc", "repeat", NULL } } },
//	{ MODKEYS,			XK_p,			spawn,		SHCMD("mpc pause; pauseallmpv") },
// neomutt_mail
//	{ MODKEY,			XK_e,			spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
// abook_contacts
//	{ MODKEYS,			XK_e,			spawn,		SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
// newsboat_rss
//	{ MODKEYS,			XK_n,			spawn,		SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
// maim_record
	{ 0,				XK_Print,		spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,		spawn,		{.v = (const char*[]){ "maimpick", NULL } } },
	{ MODKEY,			XK_Print,		spawn,		{.v = (const char*[]){ "dmenurecord", NULL } } },
	{ MODKEYS,			XK_Print,		spawn,		{.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	{ MODKEY,			XK_Delete,		spawn,		{.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	{ MODKEY,			XK_Scroll_Lock,		spawn,		SHCMD("killall screenkey || screenkey &") },
// unknown
//	{ MODKEY,			XK_minus,		spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
//	{ MODKEYS,			XK_minus,		spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
//	{ MODKEY,			XK_equal,		spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
//	{ MODKEYS,			XK_equal,		spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
//	{ MODKEYS,			XK_m,			spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
//	{ MODKEY,			XK_Insert,		spawn,		SHCMD("xdotool type $(grep -v '^#' ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },

	{ MODKEY,			XK_F1,			spawn,		SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
	{ MODKEY,			XK_F2,			spawn,		{.v = (const char*[]){ "tutorialvids", NULL } } },
	{ MODKEY,			XK_F3,			spawn,		{.v = (const char*[]){ "displayselect", NULL } } },
	{ MODKEY,			XK_F4,			spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_F5,			xrdb,		{.v = NULL } },
	{ MODKEY,			XK_F6,			spawn,		{.v = (const char*[]){ "torwrap", NULL } } },
	{ MODKEY,			XK_F7,			spawn,		{.v = (const char*[]){ "td-toggle", NULL } } },
	{ MODKEY,			XK_F8,			spawn,		{.v = (const char*[]){ "mw", "-Y", NULL } } },
	{ MODKEY,			XK_F9,			spawn,		{.v = (const char*[]){ "dmenumount", NULL } } },
	{ MODKEY,			XK_F10,			spawn,		{.v = (const char*[]){ "dmenuumount", NULL } } },
	{ MODKEY,			XK_F11,			spawn,		SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,			spawn,		SHCMD("remaps") },

	{ 0, XF86XK_AudioMute,					spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,				spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,				spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,					spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ 0, XF86XK_AudioNext,					spawn,		{.v = (const char*[]){ "mpc", "next", NULL } } },
	{ 0, XF86XK_AudioPause,					spawn,		{.v = (const char*[]){ "mpc", "pause", NULL } } },
	{ 0, XF86XK_AudioPlay,					spawn,		{.v = (const char*[]){ "mpc", "play", NULL } } },
	{ 0, XF86XK_AudioStop,					spawn,		{.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0, XF86XK_AudioRewind,				spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0, XF86XK_AudioForward,				spawn,		{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ 0, XF86XK_AudioMedia,					spawn,		{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ 0, XF86XK_AudioMicMute,				spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
//	{ 0, XF86XK_PowerOff,					spawn,		{.v = (const char*[]){ "sysact", NULL } } },
	{ 0, XF86XK_Calculator,					spawn,		{.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,					spawn,		{.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_WWW,					spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,					spawn,		{.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,				spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,					spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ 0, XF86XK_Mail,					spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,					spawn,		{.v = (const char*[]){ TERMINAL, "-e", "lfub", "/", NULL } } },
//	{ 0, XF86XK_Battery,					spawn,		SHCMD("") },
	{ 0, XF86XK_Launch1,					spawn,		{.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,				spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,				spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,					spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,				spawn,		{.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,				spawn,		{.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },

//	{ MODKEYS,			XK_b,			spawn,		SHCMD("") },
//	{ MODKEYS,			XK_c,			spawn,		SHCMD("") },
//	{ MODKEYS,			XK_s,			spawn,		SHCMD("") },
//	{ MODKEYS,			XK_x,			spawn,		SHCMD("") },
//	{ MODKEYS,			XK_z,			spawn,		SHCMD("") },
//	{ MODKEYS,			XK_apostrophe,		spawn,		SHCMD("") },
//	{ MODKEYS,			XK_backslash,		spawn,		SHCMD("") },
//	{ MODKEYS,			XK_Tab,			spawn,		SHCMD("") },
//	{ MODKEYS,			XK_Escape,		spawn,		SHCMD("") },
//	{ MODKEYS,			XK_grave,		togglescratch,	SHCMD("") },

//	{ MODKEY,			XK_h,			incrgaps,	{.i = +1 } },
//	{ MODKEY,			XK_l,			incrgaps,	{.i = -1 } },
//	{ MODKEY,			XK_h,			incrogaps,	{.i = +1 } },
//	{ MODKEY,			XK_l,			incrogaps,	{.i = -1 } },
//	{ MODKEY,			XK_h,			incrigaps,	{.i = +1 } },
//	{ MODKEY,			XK_l,			incrigaps,	{.i = -1 } },
//	{ MODKEY,			XK_0,			defaultgaps,	{0} },
//	{ MODKEY,			XK_y,			incrihgaps,	{.i = +1 } },
//	{ MODKEY,			XK_o,			incrihgaps,	{.i = -1 } },
//	{ MODKEY,			XK_y,			incrivgaps,	{.i = +1 } },
//	{ MODKEY,			XK_o,			incrivgaps,	{.i = -1 } },
//	{ MODKEY,			XK_y,			incrohgaps,	{.i = +1 } },
//	{ MODKEY,			XK_o,			incrohgaps,	{.i = -1 } },
//	{ MODKEY,			XK_y,			incrovgaps,	{.i = +1 } },
//	{ MODKEY,			XK_o,			incrovgaps,	{.i = -1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

