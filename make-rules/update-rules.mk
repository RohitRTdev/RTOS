UPDATE :=$(findstring $(TARGET),$(shell ls))
ifeq ($(UPDATE),$(TARGET))
    UPDATE :=Updating
else
    UPDATE :=Creating
endif