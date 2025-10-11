#ifndef STYXTELEGRAMBOTFRAMEWORK_TELEGRAMDATASTRUCTURE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TELEGRAMDATASTRUCTURE_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include <variant>
#include <set>

/**
 * @brief
 *   @if LANG_CN Telegram Bot API 对象的集中定义，用于在插件与框架之间共享结构化数据。
 *   @endif
 *   @if LANG_EN Centralized definitions of Telegram Bot API objects for structured data sharing between plugins and the framework.
 *   @endif
 */
namespace Telegram {
	using IntegerId = std::int64_t;
	using ChatId = std::variant<std::int64_t, std::string>;
	using FileId = std::string;
	using FileUniqueId = std::string;

	/**
	 * @brief
	 *   @if LANG_CN 表示一个表情或自定义反应的类型。
	 *   @endif
	 *   @if LANG_EN Represents the type of an emoji or custom reaction.
	 *   @endif
	 */
	struct ReactionType {
		std::string Type;
		std::optional<std::string> Emoji;
		std::optional<std::string> CustomEmojiId;
	};

	/**
	 * @brief
	 *   @if LANG_CN Telegram 用户信息。
	 *   @endif
	 *   @if LANG_EN Telegram user information.
	 *   @endif
	 */
	struct User {
		IntegerId Id = 0;
		bool IsBot = false;
		std::string FirstName;
		std::optional<std::string> LastName;
		std::optional<std::string> Username;
		std::optional<std::string> LanguageCode;
		std::optional<bool> IsPremium;
		std::optional<bool> AddedToAttachmentMenu;
		std::optional<bool> CanJoinGroups;
		std::optional<bool> CanReadAllGroupMessages;
		std::optional<bool> SupportsInlineQueries;
		/**
		 * @brief
		 *   @if LANG_CN 用户是否可以连接商业账户功能。
		 *   @endif
		 *   @if LANG_EN Indicates whether the user can connect to business features.
		 *   @endif
		 */
		std::optional<bool> CanConnectToBusiness;
	};

	/**
	 * @brief
	 *   @if LANG_CN 聊天头像信息。
	 *   @endif
	 *   @if LANG_EN Chat photo information.
	 *   @endif
	 */
	struct ChatPhoto {
		FileId SmallFileId;
		FileId BigFileId;
	};

	/**
	 * @brief
	 *   @if LANG_CN 聊天权限集合。
	 *   @endif
	 *   @if LANG_EN Chat permissions set.
	 *   @endif
	 */
	struct ChatPermissions {
		std::optional<bool> CanSendMessages;
		std::optional<bool> CanSendAudios;
		std::optional<bool> CanSendDocuments;
		std::optional<bool> CanSendPhotos;
		std::optional<bool> CanSendVideos;
		std::optional<bool> CanSendVideoNotes;
		std::optional<bool> CanSendVoiceNotes;
		std::optional<bool> CanSendPolls;
		std::optional<bool> CanSendOtherMessages;
		std::optional<bool> CanAddWebPagePreviews;
		std::optional<bool> CanChangeInfo;
		std::optional<bool> CanInviteUsers;
		std::optional<bool> CanPinMessages;
	};

	/**
	 * @brief
	 *   @if LANG_CN 描述聊天位置的经纬度信息。
	 *   @endif
	 *   @if LANG_EN Latitude and longitude describing a chat location.
	 *   @endif
	 */
	struct ChatLocation {
		double Latitude = 0.0;
		double Longitude = 0.0;
		std::optional<std::int32_t> HorizontalAccuracy;
	};

	/**
	 * @brief
	 *   @if LANG_CN 表示 Telegram 聊天对象，包括用户、群组和频道。
	 *   @endif
	 *   @if LANG_EN Represents a Telegram chat object including users, groups, and channels.
	 *   @endif
	 */
	struct Chat {
		IntegerId Id = 0;
		std::string Type;
		std::optional<std::string> Title;
		std::optional<std::string> Username;
		/**
		 * @brief
		 *   @if LANG_CN 聊天可能启用的多用户名列表。
		 *   @endif
		 *   @if LANG_EN Collection of active usernames that the chat may expose.
		 *   @endif
		 */
		std::optional<std::vector<std::string>> ActiveUsernames;
		std::optional<std::string> FirstName;
		std::optional<std::string> LastName;
		std::optional<std::string> Bio;
		std::optional<std::string> Description;
		std::optional<std::string> InviteLink;
		std::optional<ChatPhoto> Photo;
		std::optional<std::string> StickerSetName;
		std::optional<bool> CanSetStickerSet;
		std::optional<ChatPermissions> Permissions;
		std::optional<ChatLocation> Location;
		/**
		 * @brief
		 *   @if LANG_CN 使用自定义表情展示的状态标识。
		 *   @endif
		 *   @if LANG_EN Emoji identifier used for the chat's custom status.
		 *   @endif
		 */
		std::optional<std::string> EmojiStatusCustomEmojiId;
	};

	/**
	 * @brief
	 *   @if LANG_CN 表示一个 Telegram 故事内容引用。
	 *   @endif
	 *   @if LANG_EN Represents a reference to a Telegram story.
	 *   @endif
	 */
	struct Story {
		/**
		 * @brief
		 *   @if LANG_CN 故事所属的聊天信息。
		 *   @endif
		 *   @if LANG_EN Chat that owns the story.
		 *   @endif
		 */
		Chat ChatInfo;
		/**
		 * @brief
		 *   @if LANG_CN 故事实例的唯一标识。
		 *   @endif
		 *   @if LANG_EN Unique identifier of the story instance.
		 *   @endif
		 */
		std::int32_t StoryId = 0;
	};

	/**
	 * @brief
	 *   @if LANG_CN 消息实体，描述命令、URL 或格式化文本片段。
	 *   @endif
	 *   @if LANG_EN Message entity describing commands, URLs, or formatted segments.
	 *   @endif
	 */
	struct MessageEntity {
		std::string Type;
		std::int32_t Offset = 0;
		std::int32_t Length = 0;
		std::optional<std::string> Url;
		std::optional<User> UserInfo;
		std::optional<std::string> Language;
		std::optional<std::string> CustomEmojiId;
	};

	/**
	 * @brief
	 *   @if LANG_CN Telegram 中图像资源的尺寸信息。
	 *   @endif
	 *   @if LANG_EN Size information for image resources in Telegram.
	 *   @endif
	 */
	struct PhotoSize {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::int32_t Width = 0;
		std::int32_t Height = 0;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 动画消息的相关信息。
	 *   @endif
	 *   @if LANG_EN Information about an animation message.
	 *   @endif
	 */
	struct Animation {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::int32_t Width = 0;
		std::int32_t Height = 0;
		std::int32_t Duration = 0;
		std::optional<PhotoSize> Thumbnail;
		std::optional<std::string> FileName;
		std::optional<std::string> MimeType;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 音频文件信息。
	 *   @endif
	 *   @if LANG_EN Audio file information.
	 *   @endif
	 */
	struct Audio {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::int32_t Duration = 0;
		std::optional<std::string> Performer;
		std::optional<std::string> Title;
		std::optional<std::string> FileName;
		std::optional<std::string> MimeType;
		std::optional<std::int32_t> FileSize;
		std::optional<PhotoSize> Thumbnail;
	};

	/**
	 * @brief
	 *   @if LANG_CN 任意文档文件信息。
	 *   @endif
	 *   @if LANG_EN Generic document information.
	 *   @endif
	 */
	struct Document {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::optional<PhotoSize> Thumbnail;
		std::optional<std::string> FileName;
		std::optional<std::string> MimeType;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 视频文件信息。
	 *   @endif
	 *   @if LANG_EN Video file information.
	 *   @endif
	 */
	struct Video {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::int32_t Width = 0;
		std::int32_t Height = 0;
		std::int32_t Duration = 0;
		std::optional<PhotoSize> Thumbnail;
		std::optional<std::string> FileName;
		std::optional<std::string> MimeType;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 视频留言信息。
	 *   @endif
	 *   @if LANG_EN Video note information.
	 *   @endif
	 */
	struct VideoNote {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::int32_t Length = 0;
		std::int32_t Duration = 0;
		std::optional<PhotoSize> Thumbnail;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 语音消息信息。
	 *   @endif
	 *   @if LANG_EN Voice message information.
	 *   @endif
	 */
	struct Voice {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::int32_t Duration = 0;
		std::optional<std::string> MimeType;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 联系人信息。
	 *   @endif
	 *   @if LANG_EN Contact information.
	 *   @endif
	 */
	struct Contact {
		std::string PhoneNumber;
		std::string FirstName;
		std::optional<std::string> LastName;
		std::optional<IntegerId> UserId;
		std::optional<std::string> Vcard;
	};

	/**
	 * @brief
	 *   @if LANG_CN 骰子或小游戏结果。
	 *   @endif
	 *   @if LANG_EN Dice or mini game result.
	 *   @endif
	 */
	struct Dice {
		std::string Emoji;
		std::int32_t Value = 0;
	};

	/**
	 * @brief
	 *   @if LANG_CN 面具定位信息，用于贴纸。
	 *   @endif
	 *   @if LANG_EN Mask position information for stickers.
	 *   @endif
	 */
	struct MaskPosition {
		std::string Point;
		double XShift = 0.0;
		double YShift = 0.0;
		double Scale = 1.0;
	};

	/**
	 * @brief
	 *   @if LANG_CN 贴纸信息。
	 *   @endif
	 *   @if LANG_EN Sticker information.
	 *   @endif
	 */
	struct Sticker {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::string Type;
		std::int32_t Width = 0;
		std::int32_t Height = 0;
		std::optional<bool> IsAnimated;
		std::optional<bool> IsVideo;
		std::optional<std::string> ThumbFormat;
		std::optional<PhotoSize> Thumbnail;
		std::optional<std::string> Emoji;
		std::optional<std::string> SetName;
		std::optional<MaskPosition> MaskPositionInfo;
		std::optional<std::vector<std::string>> CustomEmojiId;
		std::optional<std::int32_t> FileSize;
	};

	/**
	 * @brief
	 *   @if LANG_CN 游戏信息，用于内置互动游戏。
	 *   @endif
	 *   @if LANG EN Game information for interactive games.
	 *   @endif
	 */
	struct Game {
		std::string Title;
		std::string Description;
		std::vector<PhotoSize> Photo;
		std::optional<std::string> Text;
		std::optional<std::vector<MessageEntity>> TextEntities;
		std::optional<Animation> AnimationInfo;
	};

	/**
	 * @brief
	 *   @if LANG CN 位置坐标信息。
	 *   @endif
	 *   @if LANG EN Geographic location information.
	 *   @endif
	 */
	struct Location {
		double Longitude = 0.0;
		double Latitude = 0.0;
		std::optional<double> HorizontalAccuracy;
		std::optional<std::int32_t> LivePeriod;
		std::optional<std::int32_t> Heading;
		std::optional<std::int32_t> ProximityAlertRadius;
	};

	/**
	 * @brief
	 *   @if LANG_CN 场地信息。
	 *   @endif
	 *   @if LANG_EN Venue information.
	 *   @endif
	 */
	struct Venue {
		Location VenueLocation;
		std::string Title;
		std::string Address;
		std::optional<std::string> FoursquareId;
		std::optional<std::string> FoursquareType;
		std::optional<std::string> GooglePlaceId;
		std::optional<std::string> GooglePlaceType;
	};

	/**
	 * @brief
	 *   @if LANG_CN 投票选项信息。
	 *   @endif
	 *   @if LANG EN Poll option information.
	 *   @endif
	 */
	struct PollOption {
		std::string Text;
		std::int32_t VoterCount = 0;
	};

	/**
	 * @brief
	 *   @if LANG_CN 投票回答信息。
	 *   @endif
	 *   @if LANG EN Poll answer information.
	 *   @endif
	 */
	struct PollAnswer {
		std::string PollId;
		User UserInfo;
		std::vector<std::int32_t> OptionIds;
	};

	/**
	 * @brief
	 *   @if LANG_CN 投票对象，包含问题与选项。
	 *   @endif
	 *   @if LANG EN Poll object containing a question and options.
	 *   @endif
	 */
	struct Poll {
		std::string Id;
		std::string Question;
		std::vector<PollOption> Options;
		std::optional<std::string> QuestionParseMode;
		std::optional<std::vector<MessageEntity>> QuestionEntities;
		std::int32_t TotalVoterCount = 0;
		bool IsClosed = false;
		bool IsAnonymous = true;
		std::string Type;
		bool AllowsMultipleAnswers = false;
		std::optional<std::int32_t> CorrectOptionId;
		std::optional<std::string> Explanation;
		std::optional<std::vector<MessageEntity>> ExplanationEntities;
		std::optional<std::int32_t> OpenPeriod;
		std::optional<std::int32_t> CloseDate;
	};

	/**
	 * @brief
	 *   @if LANG_CN 订单价格项。
	 *   @endif
	 *   @if LANG EN Labeled price item for invoices.
	 *   @endif
	 */
	struct LabeledPrice {
		std::string Label;
		std::int32_t Amount = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 发票信息。
	 *   @endif
	 *   @if LANG EN Invoice information.
	 *   @endif
	 */
	struct Invoice {
		std::string Title;
		std::string Description;
		std::string StartParameter;
		std::string Currency;
		std::int32_t TotalAmount = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 配送地址信息。
	 *   @endif
	 *   @if LANG EN Shipping address information.
	 *   @endif
	 */
	struct ShippingAddress {
		std::string CountryCode;
		std::string State;
		std::string City;
		std::string StreetLine1;
		std::string StreetLine2;
		std::string PostCode;
	};

	/**
	 * @brief
	 *   @if LANG_CN 配送选项。
	 *   @endif
	 *   @if LANG EN Shipping option description.
	 *   @endif
	 */
	struct ShippingOption {
		std::string Id;
		std::string Title;
		std::vector<LabeledPrice> Prices;
	};

	/**
	 * @brief
	 *   @if LANG CN 订单附加信息。
	 *   @endif
	 *   @if LANG EN Additional order information.
	 *   @endif
	 */
	struct OrderInfo {
		std::optional<std::string> Name;
		std::optional<std::string> PhoneNumber;
		std::optional<std::string> Email;
		std::optional<ShippingAddress> ShippingAddressInfo;
	};

	/**
	 * @brief
	 *   @if LANG CN 成功支付信息。
	 *   @endif
	 *   @if LANG EN Successful payment information.
	 *   @endif
	 */
	struct SuccessfulPayment {
		std::string Currency;
		std::int64_t TotalAmount = 0;
		std::string InvoicePayload;
		std::optional<std::string> ShippingOptionId;
		std::optional<OrderInfo> OrderInfoData;
		std::string TelegramPaymentChargeId;
		std::string ProviderPaymentChargeId;
	};

	/**
	 * @brief
	 *   @if LANG CN 护照文件信息。
	 *   @endif
	 *   @if LANG EN Passport file information.
	 *   @endif
	 */
	struct PassportFile {
		FileId FileIdentifier;
		std::int32_t FileSize = 0;
		std::int32_t FileDate = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 加密护照元素。
	 *   @endif
	 *   @if LANG EN Encrypted passport element.
	 *   @endif
	 */
	struct EncryptedPassportElement {
		std::string Type;
		std::optional<std::string> Data;
		std::optional<std::string> PhoneNumber;
		std::optional<std::string> Email;
		std::vector<PassportFile> Files;
		std::vector<PassportFile> FrontSide;
		std::vector<PassportFile> ReverseSide;
		std::vector<PassportFile> Selfie;
	};

	/**
	 * @brief
	 *   @if LANG CN 护照凭据。
	 *   @endif
	 *   @if LANG EN Passport credentials.
	 *   @endif
	 */
	struct EncryptedCredentials {
		std::string Data;
		std::string Hash;
		std::string Secret;
	};

	/**
	 * @brief
	 *   @if LANG CN Telegram 护照数据。
	 *   @endif
	 *   @if LANG EN Telegram passport data.
	 *   @endif
	 */
	struct PassportData {
		std::vector<EncryptedPassportElement> Data;
		EncryptedCredentials Credentials;
	};

	/**
	 * @brief
	 *   @if LANG CN 消息自动删除计时器修改。
	 *   @endif
	 *   @if LANG EN Auto delete timer change.
	 *   @endif
	 */
	struct MessageAutoDeleteTimerChanged {
		std::int32_t MessageAutoDeleteTime = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN Proximity 警报触发信息。
	 *   @endif
	 *   @if LANG EN Proximity alert triggered information.
	 *   @endif
	 */
	struct ProximityAlertTriggered {
		User Traveler;
		User Watcher;
		std::int32_t Distance = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 视频聊天调度信息。
	 *   @endif
	 *   @if LANG EN Video chat scheduled information.
	 *   @endif
	 */
	struct VideoChatScheduled {
		std::int32_t StartDate = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 视频聊天开始信息。
	 *   @endif
	 *   @if LANG EN Video chat started information.
	 *   @endif
	 */
	struct VideoChatStarted {};

	/**
	 * @brief
	 *   @if LANG CN 视频聊天结束信息。
	 *   @endif
	 *   @if LANG EN Video chat ended information.
	 *   @endif
	 */
	struct VideoChatEnded {
		std::int32_t Duration = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 视频聊天邀请用户列表。
	 *   @endif
	 *   @if LANG EN Video chat participants invited list.
	 *   @endif
	 */
	struct VideoChatParticipantsInvited {
		std::vector<User> Users;
	};

	/**
	 * @brief
	 *   @if LANG CN 用户共享信息。
	 *   @endif
	 *   @if LANG EN User shared information.
	 *   @endif
	 */
	struct UserShared {
		std::int32_t RequestId = 0;
		IntegerId SharedUserId = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 聊天共享信息。
	 *   @endif
	 *   @if LANG EN Chat shared information.
	 *   @endif
	 */
	struct ChatShared {
		std::int32_t RequestId = 0;
		ChatId SharedChatId;
	};

	/**
	 * @brief
	 *   @if LANG CN 写权限授予信息。
	 *   @endif
	 *   @if LANG EN Write access allowed information.
	 *   @endif
	 */
	struct WriteAccessAllowed {
		std::optional<std::string> WebAppName;
	};

	/**
	 * @brief
	 *   @if LANG CN 消息标识信息。
	 *   @endif
	 *   @if LANG EN Message identifier information.
	 *   @endif
	 */
	struct MessageId {
		std::int32_t MessageIdentifier = 0;
	};

	/**
	 * @brief
	 *   @if LANG CN 文件信息，可通过 getFile 获取下载链接。
	 *   @endif
	 *   @if LANG EN File information retrievable via getFile.
	 *   @endif
	 */
	struct File {
		FileId FileIdentifier;
		FileUniqueId FileUniqueIdentifier;
		std::optional<std::int32_t> FileSize;
		std::optional<std::string> FilePath;
	};

	/**
	 * @brief
	 *   @if LANG_CN Web 应用的元数据描述。
	 *   @endif
	 *   @if LANG EN Metadata describing a Web App entry point.
	 *   @endif
	 */
	struct WebAppInfo {
		/**
		 * @brief
		 *   @if LANG CN Web 应用的 HTTPS 入口地址。
		 *   @endif
		 *   @if LANG EN HTTPS entry URL for the Web App.
		 *   @endif
		 */
		std::string Url;
	};

	/**
	 * @brief
	 *   @if LANG CN 登录按钮的目标信息。
	 *   @endif
	 *   @if LANG EN Target information for a login button.
	 *   @endif
	 */
	struct LoginUrl {
		/**
		 * @brief
		 *   @if LANG CN 登录流程的 HTTPS 地址。
		 *   @endif
		 *   @if LANG EN HTTPS URL that initiates the login flow.
		 *   @endif
		 */
		std::string Url;
		/**
		 * @brief
		 *   @if LANG CN 登录后显示的替换文本。
		 *   @endif
		 *   @if LANG EN Optional text displayed after successful login.
		 *   @endif
		 */
		std::optional<std::string> ForwardText;
		/**
		 * @brief
		 *   @if LANG CN 处理授权的机器人用户名。
		 *   @endif
		 *   @if LANG EN Username of the bot that handles authorization.
		 *   @endif
		 */
		std::optional<std::string> BotUsername;
		/**
		 * @brief
		 *   @if LANG CN 是否请求授予写入权限。
		 *   @endif
		 *   @if LANG EN Whether write access should be requested.
		 *   @endif
		 */
		std::optional<bool> RequestWriteAccess;
	};

	/**
	 * @brief
	 *   @if LANG CN Inline 键盘按钮描述。
	 *   @endif
	 *   @if LANG EN Inline keyboard button description.
	 *   @endif
	 */
	struct InlineKeyboardButton {
		std::string Text;
		std::optional<std::string> Url;
		std::optional<std::string> CallbackData;
		/**
		 * @brief
		 *   @if LANG CN 登录按钮的链接信息。
		 *   @endif
		 *   @if LANG EN Login link metadata for the button.
		 *   @endif
		 */
		std::optional<LoginUrl> LoginUrlInfo;
		/**
		 * @brief
		 *   @if LANG CN 关联的 Web 应用配置。
		 *   @endif
		 *   @if LANG EN Associated Web App configuration.
		 *   @endif
		 */
		std::optional<WebAppInfo> WebApp;
		std::optional<std::string> SwitchInlineQuery;
		std::optional<std::string> SwitchInlineQueryCurrentChat;
	};

	/**
	 * @brief
	 *   @if LANG CN Inline 键盘布局。
	 *   @endif
	 *   @if LANG EN Inline keyboard markup layout.
	 *   @endif
	 */
	struct InlineKeyboardMarkup {
		std::vector<std::vector<InlineKeyboardButton>> InlineKeyboard;
	};

	/**
	 * @brief
	 *   @if LANG CN 键盘按钮投票请求类型。
	 *   @endif
	 *   @if LANG EN Keyboard button poll request type.
	 *   @endif
	 */
	struct KeyboardButtonPollType {
		std::optional<std::string> Type;
	};

	/**
	 * @brief
	 *   @if LANG CN Reply 键盘按钮描述。
	 *   @endif
	 *   @if LANG EN Reply keyboard button description.
	 *   @endif
	 */
	struct KeyboardButton {
		std::string Text;
		std::optional<bool> RequestContact;
		std::optional<bool> RequestLocation;
		std::optional<KeyboardButtonPollType> RequestPoll;
	};

	/**
	 * @brief
	 *   @if LANG CN Reply 键盘布局。
	 *   @endif
	 *   @if LANG EN Reply keyboard markup layout.
	 *   @endif
	 */
	struct ReplyKeyboardMarkup {
		std::vector<std::vector<KeyboardButton>> Keyboard;
		std::optional<bool> ResizeKeyboard;
		std::optional<bool> OneTimeKeyboard;
		std::optional<bool> Selective;
	};

	/**
	 * @brief
	 *   @if LANG CN Reply 键盘移除描述。
	 *   @endif
	 *   @if LANG EN Reply keyboard removal descriptor.
	 *   @endif
	 */
	struct ReplyKeyboardRemove {
		bool RemoveKeyboard = true;
		std::optional<bool> Selective;
	};

	/**
	 * @brief
	 *   @if LANG CN 强制回复描述。
	 *   @endif
	 *   @if LANG EN Force reply descriptor.
	 *   @endif
	 */
	struct ForceReply {
		bool ForceReplyValue = true;
		std::optional<std::string> InputFieldPlaceholder;
		std::optional<bool> Selective;
	};

	/**
	 * @brief
	 *   @if LANG CN 聊天成员信息。
	 *   @endif
	 *   @if LANG EN Chat member information.
	 *   @endif
	 */
	struct ChatMember {
		User UserInfo;
		std::string Status;
		std::optional<std::string> CustomTitle;
		std::optional<bool> IsAnonymous;
		std::optional<bool> CanBeEdited;
		std::optional<bool> CanManageChat;
		std::optional<bool> CanDeleteMessages;
		std::optional<bool> CanManageVideoChats;
		std::optional<bool> CanRestrictMembers;
		std::optional<bool> CanPromoteMembers;
		std::optional<bool> CanChangeInfo;
		std::optional<bool> CanInviteUsers;
		std::optional<bool> CanPinMessages;
		std::optional<bool> CanPostMessages;
		std::optional<bool> CanEditMessages;
	};

	/**
	 * @brief
	 *   @if LANG CN 聊天管理员权限集合。
	 *   @endif
	 *   @if LANG EN Chat administrator rights set.
	 *   @endif
	 */
	struct ChatAdministratorRights {
		bool IsAnonymous = false;
		bool CanManageChat = false;
		bool CanDeleteMessages = false;
		bool CanManageVideoChats = false;
		bool CanRestrictMembers = false;
		bool CanPromoteMembers = false;
		bool CanChangeInfo = false;
		bool CanInviteUsers = false;
		bool CanPostStories = false;
		bool CanEditStories = false;
		bool CanDeleteStories = false;
		bool CanPostMessages = false;
		bool CanEditMessages = false;
		bool CanPinMessages = false;
	};

	/**
	 * @brief
	 *   @if LANG CN 聊天成员更新事件。
	 *   @endif
	 *   @if LANG EN Chat member updated event.
	 *   @endif
	 */
	struct ChatMemberUpdated {
		Chat ChatInfo;
		User FromUser;
		std::int32_t Date = 0;
		ChatMember OldChatMember;
		ChatMember NewChatMember;
		std::optional<std::string> InviteLink;
	};

	/**
	 * @brief
	 *   @if LANG CN 聊天加入请求信息。
	 *   @endif
	 *   @if LANG EN Chat join request information.
	 *   @endif
	 */
	struct ChatJoinRequest {
		Chat ChatInfo;
		User FromUser;
		std::int32_t Date = 0;
		std::optional<std::string> Bio;
		std::optional<std::string> InviteLink;
	};

	/**
	 * @brief
	 *   @if LANG CN 消息反应更新信息。
	 *   @endif
	 *   @if LANG EN Message reaction updated information.
	 *   @endif
	 */
	struct MessageReactionUpdated {
		Chat ChatInfo;
		std::optional<User> UserInfo;
		std::optional<std::string> ChatInstance;
		std::optional<MessageId> MessageIdentifier;
		std::optional<std::string> InlineMessageId;
		std::vector<ReactionType> OldReaction;
		std::vector<ReactionType> NewReaction;
	};

	/**
	 * @brief
	 *   @if LANG CN 消息反应计数更新信息。
	 *   @endif
	 *   @if LANG EN Message reaction count updated information.
	 *   @endif
	 */
	struct MessageReactionCountUpdated {
		Chat ChatInfo;
		MessageId MessageIdentifier;
		std::int32_t Date = 0;
		std::vector<ReactionType> Reactions;
	};

	/**
	 * @brief
	 *   @if LANG CN Telegram 消息，包含文本、媒体与元数据。
	 *   @endif
	 *   @if LANG EN Telegram message containing text, media, and metadata.
	 *   @endif
	 */
	struct Message {
		std::int32_t MessageId = 0;
		Chat ChatInfo;
		std::optional<std::int32_t> MessageThreadId;
		std::optional<User> From;
		/**
		 * @brief
		 *   @if LANG_CN 表示消息是否通过内联机器人发送。
		 *   @endif
		 *   @if LANG_EN Indicates the bot through which the message was sent inline.
		 *   @endif
		 */
		std::optional<User> ViaBot;
		std::optional<User> SenderChat;
		std::optional<User> ForwardFrom;
		std::optional<Chat> ForwardFromChat;
		std::optional<std::int32_t> ForwardFromMessageId;
		std::optional<std::string> ForwardSignature;
		std::optional<std::string> ForwardSenderName;
		std::optional<std::int32_t> ForwardDate;
		std::optional<bool> IsTopicMessage;
		std::optional<bool> IsAutomaticForward;
		std::optional<std::int32_t> Date;
		std::optional<std::int32_t> EditDate;
		std::optional<bool> HasProtectedContent;
		std::optional<std::string> MediaGroupId;
		std::optional<std::string> AuthorSignature;
		std::optional<std::string> Text;
		std::optional<std::vector<MessageEntity>> Entities;
		std::optional<Animation> AnimationInfo;
		std::optional<Audio> AudioInfo;
		std::optional<Document> DocumentInfo;
		std::optional<std::vector<PhotoSize>> Photo;
		std::optional<Sticker> StickerInfo;
		std::optional<Video> VideoInfo;
		std::optional<VideoNote> VideoNoteInfo;
		std::optional<Voice> VoiceInfo;
		std::optional<std::string> Caption;
		std::optional<std::vector<MessageEntity>> CaptionEntities;
		/**
		 * @brief
		 *   @if LANG_CN 指示媒体内容是否启用了剧透遮罩。
		 *   @endif
		 *   @if LANG_EN Flags whether the media content is covered by a spoiler.
		 *   @endif
		 */
		std::optional<bool> HasMediaSpoiler;
		std::optional<Contact> ContactInfo;
		std::optional<Dice> DiceInfo;
		std::optional<Game> GameInfo;
		std::optional<Poll> PollInfo;
		std::optional<Venue> VenueInfo;
		std::optional<Location> LocationInfo;
		std::optional<std::vector<PhotoSize>> NewChatPhoto;
		std::optional<User> NewChatMember;
		std::optional<std::vector<User>> NewChatMembers;
		std::optional<User> LeftChatMember;
		std::optional<std::string> NewChatTitle;
		std::optional<MessageAutoDeleteTimerChanged> AutoDeleteTimerChanged;
		std::optional<ProximityAlertTriggered> ProximityAlertInfo;
		std::optional<VideoChatScheduled> VideoChatSchedule;
		std::optional<VideoChatStarted> VideoChatStart;
		std::optional<VideoChatEnded> VideoChatEnd;
		std::optional<VideoChatParticipantsInvited> VideoChatParticipants;
		std::optional<UserShared> UserSharedInfo;
		std::optional<ChatShared> ChatSharedInfo;
		std::optional<WriteAccessAllowed> WriteAccessInfo;
		std::optional<PassportData> PassportDataInfo;
		std::optional<Invoice> InvoiceInfo;
		std::optional<SuccessfulPayment> SuccessfulPaymentInfo;
		/**
		 * @brief
		 *   @if LANG_CN 若消息引用故事内容，则包含对应信息。
		 *   @endif
		 *   @if LANG_EN Contains story reference when the message relates to a story.
		 *   @endif
		 */
		std::optional<Story> StoryInfo;
		std::optional<InlineKeyboardMarkup> ReplyMarkup;
	};

	/**
	 * @brief
	 *   @if LANG CN 回调查询数据。
	 *   @endif
	 *   @if LANG EN Callback query data.
	 *   @endif
	 */
	struct CallbackQuery {
		std::string Id;
		User FromUser;
		std::optional<Message> MessageInfo;
		std::optional<std::string> InlineMessageId;
		std::optional<std::string> ChatInstance;
		std::optional<std::string> Data;
		std::optional<std::string> GameShortName;
	};

	/**
	 * @brief
	 *   @if LANG CN Inline 查询。
	 *   @endif
	 *   @if LANG EN Inline query information.
	 *   @endif
	 */
	struct InlineQuery {
		std::string Id;
		User FromUser;
		std::optional<Location> QueryLocation;
		std::string Query;
		std::string Offset;
	};

	/**
	 * @brief
	 *   @if LANG CN 用户选择的 Inline 结果。
	 *   @endif
	 *   @if LANG EN Chosen inline result information.
	 *   @endif
	 */
	struct ChosenInlineResult {
		std::string ResultId;
		User FromUser;
		std::optional<Location> LocationInfo;
		std::optional<std::string> InlineMessageId;
		std::string Query;
	};

	/**
	 * @brief
	 *   @if LANG CN 配送查询信息。
	 *   @endif
	 *   @if LANG EN Shipping query information.
	 *   @endif
	 */
	struct ShippingQuery {
		std::string Id;
		User FromUser;
		std::string InvoicePayload;
		ShippingAddress ShippingAddressInfo;
	};

	/**
	 * @brief
	 *   @if LANG CN 预结算查询。
	 *   @endif
	 *   @if LANG EN Pre-checkout query information.
	 *   @endif
	 */
	struct PreCheckoutQuery {
		std::string Id;
		User FromUser;
		std::string Currency;
		std::int64_t TotalAmount = 0;
		std::string InvoicePayload;
		std::optional<std::string> ShippingOptionId;
		std::optional<OrderInfo> OrderInfoData;
	};

	/**
	 * @brief
	 *   @if LANG CN Telegram 更新对象，包含所有可能的更新事件。
	 *   @endif
	 *   @if LANG EN Telegram update object containing all event variants.
	 *   @endif
	 */
	struct Update {
		std::int32_t UpdateId = 0;
		std::optional<Message> MessageInfo;
		std::optional<Message> EditedMessage;
		std::optional<Message> ChannelPost;
		std::optional<Message> EditedChannelPost;
		std::optional<InlineQuery> InlineQueryInfo;
		std::optional<ChosenInlineResult> ChosenInlineResultInfo;
		std::optional<CallbackQuery> CallbackQueryInfo;
		std::optional<ShippingQuery> ShippingQueryInfo;
		std::optional<PreCheckoutQuery> PreCheckoutQueryInfo;
		std::optional<Poll> PollInfo;
		std::optional<PollAnswer> PollAnswerInfo;
		std::optional<ChatMemberUpdated> MyChatMember;
		std::optional<ChatMemberUpdated> ChatMember;
		std::optional<ChatJoinRequest> ChatJoinRequestInfo;
		std::optional<MessageReactionUpdated> MessageReaction;
		std::optional<MessageReactionCountUpdated> MessageReactionCount;
	};

	/**
	 * @brief
	 *   @if LANG CN Webhook 配置信息。
	 *   @endif
	 *   @if LANG EN Webhook configuration information.
	 *   @endif
	 */
	struct WebhookInfo {
		std::string Url;
		bool HasCustomCertificate = false;
		std::int32_t PendingUpdateCount = 0;
		std::optional<std::string> IpAddress;
		std::optional<std::int32_t> LastErrorDate;
		std::optional<std::string> LastErrorMessage;
		std::optional<std::int32_t> LastSynchronizationErrorDate;
		std::optional<std::int32_t> MaxConnections;
		std::optional<std::set<std::string>> AllowedUpdates;
	};
}

#endif //STYXTELEGRAMBOTFRAMEWORK_TELEGRAMDATASTRUCTURE_HPP