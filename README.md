# switch-user

Switch uid,gid and groups before execute a program, of course you need to be root to do this.

The reason I create this tool because there is no tool to change uid, gid, and groups to arbitary number. `su` and `sudo` need user to be created before.

## Synopsis

    swuser <uid>[,gid][,groups][... ,groups] [the_program] [arg1] [arg2] [... argN]

uid, gid, and groups numbers are defined by list of number (separated by comma).

## Example

switch uid to 0, gid to 1, groups to 2 and 3

    # swuser 0,1,2,3 id
      uid=0 gid=1 groups=2,3

you can also use this program to add/drop some group temporary

    $ id
      uid=1000 gid=1000 groups=1000,10,100,150,1002
    $ exec sudo -E swuser 1000,100,150,1002 $SHELL
    $ id
      uid=1000 gid=1000 groups=1000,100,150,1002

if you use predefined user (e.g. daemon)

    # USER=daemon LOGNAME=daemon HOME=/tmp/daemon swuser $(id -u daemon),$(id -G daemon | tr ' ' ,) bash
