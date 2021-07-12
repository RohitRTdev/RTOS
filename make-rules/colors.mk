
PRETTY_PRINT =ENABLE #Note that this is overriden by command line argument
RED :=\e[31m
YELLOW :=\e[33m
GREEN :=\e[32m
CYAN :=\e[36m
BLUE :=\e[94m
END :=\e[0m
BOLD :=\e[1m

#disable pretty printing
ifeq ($(PRETTY_PRINT),DISABLE)
	RED :=
	YELLOW :=
	GREEN :=
	CYAN :=
	BLUE :=
	END :=
	BOLD :=
endif

export RED BLUE END BOLD YELLOW GREEN CYAN