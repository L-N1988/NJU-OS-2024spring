#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>

#define MAXBUF 128
#define MAXPID 1024

typedef struct proc {
  int pid;             // Process ID
  int ppid;            // Parent process ID
  char name[16];       // Process name
} proc;

// helper functions
int process(proc *, int);
int lsproc(proc *);
int pstree(proc *, int, int, char *);
int cmpfunc(const void *, const void *);

enum order {bypid, byname};
enum order treeOrder = byname; // default processes sorted by name in increasing order
bool showpid = false;

int main(int argc, char *argv[]) {
  proc *pids = (proc *)malloc(MAXPID * sizeof(proc));
  int nproc = 0;
  if ((nproc = lsproc(pids)) <= 0) {
    return -1; // read procfs failed
  }

  // pasrse opts, switch case
  int opt;
  static struct option long_options[] = {{"show-pids", no_argument, 0, 'p'},
                                         {"numeric-sort", no_argument, 0, 'n'},
                                         {"version", no_argument, 0, 'V'},
                                         {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "pnV", long_options, NULL)) != -1) {
    // -p or --show-pids
    // -n or --numeric-sort
    // -V or --version
    switch (opt) {
    case 'p':
      printf("show pids\n");
      // assume all pids in array are sorted by increased order
      showpid = true;
      break;
    case 'n':
      printf("numeric sort pids\n");
      treeOrder = bypid;
      break;
    case 'V':
      fprintf(stderr, "pstree 0.01\nCopyright (C) 2024 Matrix\n");
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-p] [-n] [-V]\n", argv[0]);
      break;
    }
  }

  proc *root = (proc *)malloc(sizeof(proc));
  if (process(root, 1) > -1) {
    if (showpid) {
      printf("%s[%d]\n", root->name, root->pid);
    } else {
      printf("%s\n", root->name);
    }
  }
  free(root);

  pstree(pids, nproc, 1, "");
  free(pids);
  return 0;
}

// constructor of proc
int process(proc *p, int pid) {
  if (pid == 0) {
    return -1;
  }
  char procname[32];
  snprintf(procname, sizeof(procname), "/proc/%u/status", pid);
  FILE *fp = fopen(procname, "r");
  assert(fp);
  char status[MAXBUF];
  if (fp && fread(status, sizeof(char), MAXBUF - 1, fp)) {
    char *ppid_ptr = strstr(status, "PPid:");
    char *pname_ptr = strstr(status, "Name:");

    // find success: not returen 0 or EOF(-1, not found)
    if (sscanf(ppid_ptr, "PPid:%d", &p->ppid) > 0 &&
        sscanf(pname_ptr, "Name:%s", p->name) > 0) {
      // printf("DEBUG: pid: %d, name: %s, ppid: %d\n", pid, p->name, p->ppid);
      p->pid = pid;
      return 0;
    }
  }
  fclose(fp);

  return -1;
}

// list all processes folder (aka, all pids)
int lsproc(proc *procs) {
  struct dirent *pDirent;
  DIR *pDir;
  int pid;
  int nproc = 0;

  pDir = opendir("/proc");
  if (pDir == NULL) {
    printf("Cannot open directory '/proc'\n");
    return 0;
  }

  while ((pDirent = readdir(pDir)) != NULL) {
    // folder is named by number (pid)
    if (sscanf(pDirent->d_name, "%d", &pid) > 0) {
      // printf("PID: %d\n", pid);
      assert(nproc < MAXPID);
      if (process(procs + nproc, pid) != -1) {
        nproc += 1;
      } else {
        return -1;
      }
    }
  }
  closedir(pDir);

  return nproc;
}

int pstree(proc *procs, int npid, int pid, char *prefix) {
  char *pointer, *segment;
  proc *child = NULL;
  proc *childs = (proc *) malloc(npid * sizeof(proc));
  int nchild = 0;

  for (int i = 0; i < npid; i++) {
    child = procs + i;
    if (child->ppid == pid) {
      childs[nchild] = *child; // DONE: can struct assign values directly??? YES!!!
      nchild += 1;
    }
  }

  if (treeOrder == byname) {
    // pstree sorted by name then by pid
    qsort(childs, nchild, sizeof(proc), cmpfunc);
  } else {
    // PASS: pstree sorted by pid by default
    ;
  }

  // pstree sorted by pid
  for (int i = 0; i < nchild; i++) {
    if (i == nchild - 1) {
      pointer = "└── ";
      segment = "    ";
    } else {
      pointer = "├── ";
      segment = "│   ";
    }

    // pre-order traverse process tree
    if (showpid) {
      printf("%s%s%s[%d]\n", prefix, pointer, childs[i].name, childs[i].pid);
    } else {
      printf("%s%s%s\n", prefix, pointer, childs[i].name);
    }

    char *next_prefix = (char *)malloc(strlen(prefix) + strlen(segment) + 1);
    sprintf(next_prefix, "%s%s", prefix, segment);
    pstree(procs, npid, childs[i].pid, next_prefix);
    free(next_prefix);
  }

  free(childs);

  return 0;
}

int cmpfunc(const void * a, const void * b) {
  if (strcmp(((proc *)a)->name, ((proc *)b)->name) != 0) {
    return strcmp(((proc *)a)->name, ((proc *)b)->name) > 0;
  } else {
    return ((proc *)a)->pid - ((proc *)b)->pid;
  }
}
