# disable verbose builds by default
# If you want to see all the gory details of the build process,
# run "V=1 make <target>"

AM_DEFAULT_V=0

AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_V))
am__v_CC_0 = @echo "  CC      " $$@;
am__v_CC_1 = 

AM_V_AS = $(am__v_AS_$(V))
am__v_AS_ = $(am__v_AS_$(AM_DEFAULT_V))
am__v_AS_0 = @echo "  AS      " $$@;
am__v_AS_1 = 

AM_V_AR = $(am__v_AR_$(V))
am__v_AR_ = $(am__v_AR_$(AM_DEFAULT_V))
am__v_AR_0 = @echo "  AR      " $$@;
am__v_AR_1 = 

AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_V))
am__v_at_0 = @
am__v_at_1 = 


