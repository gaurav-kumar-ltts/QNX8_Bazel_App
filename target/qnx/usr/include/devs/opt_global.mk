# feature flags
CCFLAGS +=	-DSMP \
			-DEARLY_AP_STARTUP \
			-DVIMAGE \
			-DALTQ \
			-DDEV_NETMAP \

# There's nothing we want from <strings.h>.
# In particular we don't want it to define bcopy -> memmove.
# We want bcopy -> memcpy from "sys/systm.h".  Catch any
# potential occurances of the former.
# We also don't want unistd.h from the SDP except for a
# few special cases.
CCFLAGS += -D_STRINGS_H_INCLUDED -D_UNISTD_H_INCLUDED
