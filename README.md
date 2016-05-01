# switch-user

switch uid,gid and groups

just run `make` to build it

## synopsis

    swuser <uid>[,gid][,groups]... [cmd] [args]...

## example

    # swuser 0,1,2,3 id
      uid=0 gid=1 groups=2,3
