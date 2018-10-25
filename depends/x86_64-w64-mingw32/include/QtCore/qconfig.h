#define QT_VERSION_MAJOR    5
#define QT_VERSION_MINOR    7
#define QT_VERSION_PATCH    1
#define QT_VERSION_STR      "5.7.1"

/* Everything */
/* Compile time features */
/* Qt was configured for a static build */
#if !defined(QT_SHARED) && !defined(QT_STATIC)
# define QT_STATIC
#endif


// Compiler sub-arch support
#define QT_COMPILER_SUPPORTS_SSE2 1
#define QT_COMPILER_SUPPORTS_SSE3 1
#define QT_COMPILER_SUPPORTS_SSSE3 1
#define QT_COMPILER_SUPPORTS_SSE4_1 1
#define QT_COMPILER_SUPPORTS_SSE4_2 1
#define QT_COMPILER_SUPPORTS_AVX 1
#define QT_COMPILER_SUPPORTS_AVX2 1

#ifndef QT_BOOTSTRAPPED

#if defined(QT_LINKED_OPENSSL) && defined(QT_NO_LINKED_OPENSSL)
# undef QT_LINKED_OPENSSL
#elif !defined(QT_LINKED_OPENSSL) && !defined(QT_NO_LINKED_OPENSSL)
# define QT_LINKED_OPENSSL
#endif

#if defined(QT_NO_ALSA) && defined(QT_ALSA)
# undef QT_NO_ALSA
#elif !defined(QT_NO_ALSA) && !defined(QT_ALSA)
# define QT_NO_ALSA
#endif

#if defined(QT_NO_CUPS) && defined(QT_CUPS)
# undef QT_NO_CUPS
#elif !defined(QT_NO_CUPS) && !defined(QT_CUPS)
# define QT_NO_CUPS
#endif

#if defined(QT_NO_EGL) && defined(QT_EGL)
# undef QT_NO_EGL
#elif !defined(QT_NO_EGL) && !defined(QT_EGL)
# define QT_NO_EGL
#endif

#if defined(QT_NO_EGLFS) && defined(QT_EGLFS)
# undef QT_NO_EGLFS
#elif !defined(QT_NO_EGLFS) && !defined(QT_EGLFS)
# define QT_NO_EGLFS
#endif

#if defined(QT_NO_EGL_X11) && defined(QT_EGL_X11)
# undef QT_NO_EGL_X11
#elif !defined(QT_NO_EGL_X11) && !defined(QT_EGL_X11)
# define QT_NO_EGL_X11
#endif

#if defined(QT_NO_EVDEV) && defined(QT_EVDEV)
# undef QT_NO_EVDEV
#elif !defined(QT_NO_EVDEV) && !defined(QT_EVDEV)
# define QT_NO_EVDEV
#endif

#if defined(QT_NO_EVENTFD) && defined(QT_EVENTFD)
# undef QT_NO_EVENTFD
#elif !defined(QT_NO_EVENTFD) && !defined(QT_EVENTFD)
# define QT_NO_EVENTFD
#endif

#if defined(QT_NO_FONTCONFIG) && defined(QT_FONTCONFIG)
# undef QT_NO_FONTCONFIG
#elif !defined(QT_NO_FONTCONFIG) && !defined(QT_FONTCONFIG)
# define QT_NO_FONTCONFIG
#endif

#if defined(QT_NO_FREETYPE) && defined(QT_FREETYPE)
# undef QT_NO_FREETYPE
#elif !defined(QT_NO_FREETYPE) && !defined(QT_FREETYPE)
# define QT_NO_FREETYPE
#endif

#if defined(QT_NO_GETIFADDRS) && defined(QT_GETIFADDRS)
# undef QT_NO_GETIFADDRS
#elif !defined(QT_NO_GETIFADDRS) && !defined(QT_GETIFADDRS)
# define QT_NO_GETIFADDRS
#endif

#if defined(QT_NO_GLIB) && defined(QT_GLIB)
# undef QT_NO_GLIB
#elif !defined(QT_NO_GLIB) && !defined(QT_GLIB)
# define QT_NO_GLIB
#endif

#if defined(QT_NO_ICONV) && defined(QT_ICONV)
# undef QT_NO_ICONV
#elif !defined(QT_NO_ICONV) && !defined(QT_ICONV)
# define QT_NO_ICONV
#endif

#if defined(QT_NO_INOTIFY) && defined(QT_INOTIFY)
# undef QT_NO_INOTIFY
#elif !defined(QT_NO_INOTIFY) && !defined(QT_INOTIFY)
# define QT_NO_INOTIFY
#endif

#if defined(QT_NO_IPV6IFNAME) && defined(QT_IPV6IFNAME)
# undef QT_NO_IPV6IFNAME
#elif !defined(QT_NO_IPV6IFNAME) && !defined(QT_IPV6IFNAME)
# define QT_NO_IPV6IFNAME
#endif

#if defined(QT_NO_LIBPROXY) && defined(QT_LIBPROXY)
# undef QT_NO_LIBPROXY
#elif !defined(QT_NO_LIBPROXY) && !defined(QT_LIBPROXY)
# define QT_NO_LIBPROXY
#endif

#if defined(QT_NO_MITSHM) && defined(QT_MITSHM)
# undef QT_NO_MITSHM
#elif !defined(QT_NO_MITSHM) && !defined(QT_MITSHM)
# define QT_NO_MITSHM
#endif

#if defined(QT_NO_MREMAP) && defined(QT_MREMAP)
# undef QT_NO_MREMAP
#elif !defined(QT_NO_MREMAP) && !defined(QT_MREMAP)
# define QT_NO_MREMAP
#endif

#if defined(QT_NO_NATIVE_POLL) && defined(QT_NATIVE_POLL)
# undef QT_NO_NATIVE_POLL
#elif !defined(QT_NO_NATIVE_POLL) && !defined(QT_NATIVE_POLL)
# define QT_NO_NATIVE_POLL
#endif

#if defined(QT_NO_OPENGL) && defined(QT_OPENGL)
# undef QT_NO_OPENGL
#elif !defined(QT_NO_OPENGL) && !defined(QT_OPENGL)
# define QT_NO_OPENGL
#endif

#if defined(QT_NO_OPENVG) && defined(QT_OPENVG)
# undef QT_NO_OPENVG
#elif !defined(QT_NO_OPENVG) && !defined(QT_OPENVG)
# define QT_NO_OPENVG
#endif

#if defined(QT_NO_POSIX_FALLOCATE) && defined(QT_POSIX_FALLOCATE)
# undef QT_NO_POSIX_FALLOCATE
#elif !defined(QT_NO_POSIX_FALLOCATE) && !defined(QT_POSIX_FALLOCATE)
# define QT_NO_POSIX_FALLOCATE
#endif

#if defined(QT_NO_PRINTDIALOG) && defined(QT_PRINTDIALOG)
# undef QT_NO_PRINTDIALOG
#elif !defined(QT_NO_PRINTDIALOG) && !defined(QT_PRINTDIALOG)
# define QT_NO_PRINTDIALOG
#endif

#if defined(QT_NO_PRINTER) && defined(QT_PRINTER)
# undef QT_NO_PRINTER
#elif !defined(QT_NO_PRINTER) && !defined(QT_PRINTER)
# define QT_NO_PRINTER
#endif

#if defined(QT_NO_PULSEAUDIO) && defined(QT_PULSEAUDIO)
# undef QT_NO_PULSEAUDIO
#elif !defined(QT_NO_PULSEAUDIO) && !defined(QT_PULSEAUDIO)
# define QT_NO_PULSEAUDIO
#endif

#if defined(QT_NO_STYLE_WINDOWSCE) && defined(QT_STYLE_WINDOWSCE)
# undef QT_NO_STYLE_WINDOWSCE
#elif !defined(QT_NO_STYLE_WINDOWSCE) && !defined(QT_STYLE_WINDOWSCE)
# define QT_NO_STYLE_WINDOWSCE
#endif

#if defined(QT_NO_STYLE_WINDOWSMOBILE) && defined(QT_STYLE_WINDOWSMOBILE)
# undef QT_NO_STYLE_WINDOWSMOBILE
#elif !defined(QT_NO_STYLE_WINDOWSMOBILE) && !defined(QT_STYLE_WINDOWSMOBILE)
# define QT_NO_STYLE_WINDOWSMOBILE
#endif

#if defined(QT_NO_TSLIB) && defined(QT_TSLIB)
# undef QT_NO_TSLIB
#elif !defined(QT_NO_TSLIB) && !defined(QT_TSLIB)
# define QT_NO_TSLIB
#endif

#if defined(QT_NO_XRENDER) && defined(QT_XRENDER)
# undef QT_NO_XRENDER
#elif !defined(QT_NO_XRENDER) && !defined(QT_XRENDER)
# define QT_NO_XRENDER
#endif

#if defined(QT_NO_ZLIB) && defined(QT_ZLIB)
# undef QT_NO_ZLIB
#elif !defined(QT_NO_ZLIB) && !defined(QT_ZLIB)
# define QT_NO_ZLIB
#endif

#if defined(QT_RUNTIME_XCURSOR) && defined(QT_NO_RUNTIME_XCURSOR)
# undef QT_RUNTIME_XCURSOR
#elif !defined(QT_RUNTIME_XCURSOR) && !defined(QT_NO_RUNTIME_XCURSOR)
# define QT_RUNTIME_XCURSOR
#endif

#if defined(QT_RUNTIME_XFIXES) && defined(QT_NO_RUNTIME_XFIXES)
# undef QT_RUNTIME_XFIXES
#elif !defined(QT_RUNTIME_XFIXES) && !defined(QT_NO_RUNTIME_XFIXES)
# define QT_RUNTIME_XFIXES
#endif

#if defined(QT_RUNTIME_XRANDR) && defined(QT_NO_RUNTIME_XRANDR)
# undef QT_RUNTIME_XRANDR
#elif !defined(QT_RUNTIME_XRANDR) && !defined(QT_NO_RUNTIME_XRANDR)
# define QT_RUNTIME_XRANDR
#endif

#endif // QT_BOOTSTRAPPED

#define QT_QPA_DEFAULT_PLATFORM_NAME "windows"
