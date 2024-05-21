### Description

Even though JPEGs are more complicated than BMPs, JPEGs have “signatures,” patterns of bytes that can distinguish them from other file formats. Specifically, the first three bytes of JPEGs are `0xff 0xd8 0xff`

Odds are, if I find this pattern of four bytes on media known to store photos (e.g., my memory card), they demarcate the start of a JPEG. To be fair, I might encounter these patterns on some disk purely by chance, so data recovery isn’t an exact science.

Digital cameras tend to store photographs contiguously on memory cards, whereby each photo is stored immediately after the previously taken photo. Accordingly, the start of a JPEG usually demarks the end of another. However, digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B). The implication is that these cameras only write to those cards in units of 512 B. A photo that’s 1 MB (i.e., 1,048,576 B) thus takes up 1048576 ÷ 512 = 2048 “blocks” on a memory card. But so does a photo that’s, say, one byte smaller (i.e., 1,048,575 B)! The wasted space on disk is called “slack space.” Forensic investigators often look at slack space for remnants of suspicious data.

The implication of all these details is that me, the investigator, can probably write a program that iterates over a copy of my memory card, looking for JPEGs’ signatures. Each time I find a signature, I can open a new file for writing and start filling that file with bytes from my memory card, closing that file only once I encounter another signature. Moreover, rather than read your memory card’s bytes one at a time, I can read 512 of them at a time into a buffer for efficiency’s sake. Thanks to FAT, I can trust that JPEGs’ signatures will be “block-aligned.” That is, I only need to look for those signatures in a block’s first four bytes.

Realize, of course, that JPEGs can span contiguous blocks. Otherwise, no JPEG could be larger than 512 B. But the last byte of a JPEG might not fall at the very end of a block. Recall the possibility of slack space. But not to worry. Because this memory card was brand-new when you started snapping photos, odds are it’d been “zeroed” (i.e., filled with 0s) by the manufacturer, in which case any slack space will be filled with 0s. It’s okay if those trailing 0s end up in the JPEGs I recover; they should still be viewable.

<div>
    <img src="https://github.com/AHMEDELZARIA/Recover-JPEG/assets/93144563/03ae0dd9-b139-451a-b7ec-7de95fcdbd66" alt="pexels-pixabay-414781">
</div>
