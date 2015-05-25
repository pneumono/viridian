# viridian
This repository contains various scripts, hacky one-liners, and other miscellaneous stuff I've written to manage my servers under the viridian.io name. There is currently no setup script (as most of the scripts are synced between boxes using unison), and it probably doesn't make much sense to try and use this outside of the ecosystem of my servers (at least not until I rewrite most of it)

Currently this repo contains:

 - script to check which programs are listening on what ports in a pretty columnated way
 - message of the day binaries, written in c++, compiled for armv7 and x86_64 (source is in src/)
 - a very very hacky script that gets a list of current clients from pritunl (web-based frontend for OpenVPN) and updates dnsmasq with DNS entries for all hosts
 - a central viridian script, meant to encompass everything else. currently it only handles listing and banning of clients who have failed ssh authentication more than 20 times
 - a script to sync the /viridian folder across all of my servers
 - a list of IPs banned by the viridian script above across all servers (need a better way to centralize that)
 - a custom bashrc that sets several shortcuts and environment variables, including my custom prompt
 - a list of hosts (obtained from the pritunl script) that is symlinked to /etc/vir-hosts so dnsmasq knows where everyone is

Things upcoming, maybe:

 - setup script so this can be used on servers other than my own (and with other SSL keys)
 - centralization of most of the other stuff into bin/viridian, just to keep it simple
 - general cleanup
 - probably other stuff
