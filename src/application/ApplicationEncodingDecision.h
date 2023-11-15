#ifndef APPLICATION_ENCODING_DECISION
#define APPLICATION_ENCODING_DECISION

#include <string>
#include <vector>

class ApplicationEncodingDecision {
public:
    ApplicationEncodingDecision();
    ~ApplicationEncodingDecision();

    std::vector<std::string> audioStreams;
    /* The user's desired encoder */
    std::string wantedEncoder;
    /* The current encoder being used */
    std::string runningEncoder;
    /* The current decoder being used */
    std::string runningDecoder;
    /* Defined MediaFormat quality */
    std::string quality;
    /* Codec tune setting */
    std::string tune;
    /* Start the video from this time */
    std::string startBeginning;
    /* Trim the video to this time */
    std::string trim;

    /* Amount of concurrent conversions */
    int amount;
    /* CRF override */
    int crfOverride;

    /* Crop the video */
    bool crop;
    /* Use bitrate instead of CRF */
    bool useBitrate;
    /* Use strict bitrate values instead of variable */
    bool useConstrain;
    /* Validate the video after conversion */
    bool validate;
    /* Use hardware decode */
    bool useHardwareDecode;
    /* Use hardware encode */
    bool useHardwareEncode;
    /* Overwrite existing file */
    bool overwrite;

    void validateSettings();

private:
};

#endif //! APPLICATION_ENCODING_DECISION
