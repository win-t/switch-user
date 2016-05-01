# switch-user

switch uid,gid and groups

just run `make` to build it

## synopsis

    swuser <uid>[,gid][,groups]... [cmd] [args]...

## example

switch uid to 0, gid to 1, groups to 2 and 3

    # swuser 0,1,2,3 id
      uid=0 gid=1 groups=2,3

you can also use this program to drop some group temporary

    $ id
      uid=1000 gid=1000 groups=1000,10,100,150,1002
    $ exec sudo -E swuser 1000,100,150,1002
    $ id
      uid=1000 gid=1000 groups=1000,100,150,1002
