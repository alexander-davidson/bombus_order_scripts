rm(list = ls())

# setwd
setwd()

my_data <- read.csv('output_27_jan.txt', sep = ',', header = T) # load correct data

# remove 1st row
my_data <- my_data[-1, ] 

# change column name (remove capital)
names(my_data)[names(my_data) == 'Date'] = 'date'

# keep only id and timestamp
my_data <- my_data[ , c('number', 'date')]

# convert ids to string and date to datatype: date
my_data$date <- as.POSIXlt(my_data$date, format = "%d-%b-%Y %H:%M:%S")

# remove entries that fall within an exclusion window of time
to_keep <- logical(nrow(my_data)) # make logical (bool) list length of my_data
last_capture <- my_data$date[1] # make variable to keep the most recent capture
to_keep[1] <- T # set the first capture to TRUE
excl_window <- 30 # set the time window to exclude captures

for (i in 2:nrow(my_data)) {
  
  if (difftime(my_data$date[i], last_capture, units = 'secs') >= excl_window) { # check if difference between last capture and current row is >= to the exclusion window
    to_keep[i] <- T # if so, mark the bool-list as T
    last_capture <- my_data$date[i] # update the last capture variable
  } else {
    to_keep[i] <- F # otherwise mark it as false
  }
  
}

my_data <- my_data[to_keep, ] # update dataframe only with rows at index of bool-list == TRUE

# remove ids with less that 10 captures
to_remove <- vector()
for (i in my_data$number) {
  if (nrow(my_data[my_data$number == i, ]) < 10) {
    to_remove <- append(to_remove, i)
  }
}

`%nin%` <- Negate(`%in%`) # creates 'not it'
my_data <- subset(my_data, number %nin% to_remove) # remove those ids


check_bee <- function(id) {
  bee_data <- my_data[my_data$number == id, ]
  caps <- nrow(bee_data)
  
  today_data <- bee_data[bee_data$date$mday == as.POSIXlt(Sys.time())$mday, ]
  today_caps <- nrow(today_data)
  
  print(paste('total captures for bee', id, ':', caps, 'and total captures today:', today_caps))
}





