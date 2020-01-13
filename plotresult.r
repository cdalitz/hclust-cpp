#
# Plot the two line segment clusters in red/blue
#


x <- read.csv(file("stdin"), header=FALSE)

sysname <- Sys.info()[['sysname']]
if (sysname == "Darwin") {
  quartz()
} else if (sysname == "Windows") {
  windows()
} else {
  x11()
}
x0 <- x[x[,5]==0,]
x1 <- x[x[,5]==1,]
plot(c(x0[,1],x0[,3]), c(x0[,2],x0[,4]), asp=1, col="red", xlab=NA, ylab=NA, main="Clustering Result")
points(c(x1[,1],x1[,3]), c(x1[,2],x1[,4]), asp=1, col="blue")
segments(x0[,1], x0[,2], x0[,3], x0[,4], col="red")
segments(x1[,1], x1[,2], x1[,3], x1[,4], col="blue")

# keep window open
while (!is.null(dev.list())) Sys.sleep(1)
#locator()
