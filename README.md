# TrafficSignsRecognitionSystem
C++ implementation of a traffic signs recognition systetem based on a paper "Dyczkowski, K., Gadecki, P., & Kułakowski, A. (2011, May). Traffic signs recognition system. In Proceedings of the World Conference on Soft Computing, San Francisco State University, USA."

Pipeline: image -> HSV conversion -> Segmentation -> Improve segmentation by using a set of fuzzy rules. Connect parts of the same image. Discard wrong contours. -> Encode images. Some value corresponds to a pixel color. Divide image into subsets, then encode those subsets -> Compare encoding output (vectors of values) to a database. 
