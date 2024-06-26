NEWTOY(toybox, NULL, 0)
USE_BASENAME(NEWTOY(basename, "<1>2", TOYFLAG_BIN))
USE_BZCAT(NEWTOY(bzcat, NULL, TOYFLAG_USR|TOYFLAG_BIN))
USE_CAT(NEWTOY(cat, "u", TOYFLAG_BIN))
USE_CATV(NEWTOY(catv, "vte", TOYFLAG_USR|TOYFLAG_BIN))
USE_TOYSH(NEWTOY(cd, NULL, TOYFLAG_NOFORK))
USE_CHROOT(NEWTOY(chroot, "^<1", TOYFLAG_USR|TOYFLAG_SBIN))
USE_CHVT(NEWTOY(chvt, "<1", TOYFLAG_USR|TOYFLAG_SBIN))
USE_CKSUM(NEWTOY(cksum, "IPLN", TOYFLAG_BIN))
USE_COUNT(NEWTOY(count, NULL, TOYFLAG_USR|TOYFLAG_BIN))
USE_CP(NEWTOY(cp, "<2vslrR+rdpa+d+p+rHLPif", TOYFLAG_BIN))
USE_DF(NEWTOY(df, "Pkt*a", TOYFLAG_USR|TOYFLAG_SBIN))
USE_DIRNAME(NEWTOY(dirname, "<1>1", TOYFLAG_BIN))
USE_DMESG(NEWTOY(dmesg, "s#n#c", TOYFLAG_BIN))
USE_ECHO(NEWTOY(echo, "^?en", TOYFLAG_BIN))
USE_TOYSH(NEWTOY(exit, NULL, TOYFLAG_NOFORK))
USE_FALSE(NEWTOY(false, NULL, TOYFLAG_BIN))
USE_HELLO(NEWTOY(hello, "e@d*c#b:a", TOYFLAG_USR|TOYFLAG_BIN))
USE_HELP(NEWTOY(help, "<1", TOYFLAG_BIN))
USE_MDEV(NEWTOY(mdev, "s", TOYFLAG_USR|TOYFLAG_BIN|TOYFLAG_UMASK))
USE_MKE2FS(NEWTOY(mke2fs, "<1>2g:Fnqm#N#i#b#", TOYFLAG_SBIN))
USE_MKFIFO(NEWTOY(mkfifo, "<1m:", TOYFLAG_BIN|TOYFLAG_UMASK))
USE_MKSWAP(NEWTOY(mkswap, "<1>2", TOYFLAG_SBIN))
USE_NETCAT(OLDTOY(nc, netcat, USE_NETCAT_LISTEN("tl^L^")"w#p#s:q#f:", TOYFLAG_BIN))
USE_NETCAT(NEWTOY(netcat, USE_NETCAT_LISTEN("tl^L^")"w#p#s:q#f:", TOYFLAG_BIN))
USE_ONEIT(NEWTOY(oneit, "^<1c:p", TOYFLAG_SBIN))
USE_PATCH(NEWTOY(patch, "up#i:R", TOYFLAG_USR|TOYFLAG_BIN))
USE_PWD(NEWTOY(pwd, NULL, TOYFLAG_BIN))
USE_READLINK(NEWTOY(readlink, "<1f", TOYFLAG_BIN))
USE_RMDIR(NEWTOY(rmdir, "<1p", TOYFLAG_BIN))
USE_SED(NEWTOY(sed, "irne*", TOYFLAG_BIN))
USE_SEQ(NEWTOY(seq, "<1>3?", TOYFLAG_USR|TOYFLAG_BIN))
USE_TOYSH(OLDTOY(sh, toysh, "c:i", TOYFLAG_BIN))
USE_SHA1SUM(NEWTOY(sha1sum, NULL, TOYFLAG_USR|TOYFLAG_BIN))
USE_SLEEP(NEWTOY(sleep, "<1", TOYFLAG_BIN))
USE_SORT(NEWTOY(sort, USE_SORT_BIG("S:T:m" "o:k*t:bgMcszdfi") "run", TOYFLAG_USR|TOYFLAG_BIN))
USE_SYNC(NEWTOY(sync, NULL, TOYFLAG_BIN))
USE_TEE(NEWTOY(tee, "ia", TOYFLAG_BIN))
USE_TOUCH(NEWTOY(touch, "l#t:r:mca", TOYFLAG_BIN|TOYFLAG_UMASK))
USE_TOYSH(NEWTOY(toysh, "c:i", TOYFLAG_BIN))
USE_TRUE(NEWTOY(true, NULL, TOYFLAG_BIN))
USE_TTY(NEWTOY(tty, "s", TOYFLAG_BIN))
USE_UNAME(NEWTOY(uname, "amvrns", TOYFLAG_BIN))
USE_WHICH(NEWTOY(which, "<1a", TOYFLAG_USR|TOYFLAG_BIN))
USE_YES(NEWTOY(yes, NULL, TOYFLAG_USR|TOYFLAG_BIN))
