rm(list = ls())

setwd("D:/Order_Discrimination_Bombus/qr_data")

t = read.table('output.txt', sep = ',', header = TRUE)


t = t[-1, c('number', 'Date')]

checkExposure = function(x){
  print(paste0('Bee ', x, ' Captured for ', nrow(t[t$number == x, ]), ' frames'))
}


# 24576 false exposure on 25/07
checkExposure(5617)
